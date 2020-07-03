/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_user_model/browser/user_model_file_service.h"

#include "base/bind.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/json/json_reader.h"
#include "base/logging.h"
#include "base/strings/stringprintf.h"
#include "base/task/post_task.h"
#include "brave/components/brave_user_model/browser/region_util.h"
#include "brave/components/l10n/browser/locale_helper.h"

namespace brave_user_model {

namespace {

const uint16_t kCurrentSchemaVersion = 1;
const char kSchemaVersionPath[] = "schemaVersion";

const char kModelsPath[] = "models";
const char kModelsIdPath[] = "id";
const char kModelsFilenamePath[] = "filename";
const char kModelsVersionPath[] = "version";

const char kComponentName[] = "Brave User Model Updater (%s)";
const base::FilePath::CharType kManifestFile[] =
    FILE_PATH_LITERAL("models.json");

}  // namespace

UserModelFileService::UserModelFileService(
    Delegate* delegate)
    : brave_component_updater::BraveComponent(delegate) {
  DCHECK(delegate);

  const std::string locale =
      brave_l10n::LocaleHelper::GetInstance()->GetLocale();
  const std::string country_code =
      brave_l10n::LocaleHelper::GetCountryCode(locale);

  const auto& region = GetRegionInfo(country_code);
  if (!region) {
    VLOG(1) << country_code << " not supported for user model updater";
    return;
  }

  VLOG(1) << country_code << " supported for user model updater";

  Register(base::StringPrintf(kComponentName, country_code.c_str()),
      region->component_id, region->component_base64_public_key);
}

UserModelFileService::~UserModelFileService() = default;

std::string GetManifest(
    const base::FilePath& path) {
  std::string json;

  const bool success = base::ReadFileToString(path, &json);
  if (!success || json.empty()) {
    VLOG(1) << "Failed to read manifest file: " << path;
    return json;
  }

  return json;
}

void UserModelFileService::OnComponentReady(
    const std::string& component_id,
    const base::FilePath& install_dir,
    const std::string& manifest) {
  base::PostTaskAndReplyWithResult(FROM_HERE,
      { base::ThreadPool(), base::MayBlock() },
      base::BindOnce(&GetManifest, install_dir.Append(kManifestFile)),
      base::BindOnce(&UserModelFileService::OnGetManifest,
          weak_factory_.GetWeakPtr(), install_dir));
}

void UserModelFileService::OnGetManifest(
    const base::FilePath& install_dir,
    const std::string& json) {
  base::Optional<base::Value> manifest = base::JSONReader::Read(json);
  if (!manifest) {
    VLOG(1) << "Failed to parse user model manifest";
    return;
  }

  const base::Optional<int> version = manifest->FindIntPath(kSchemaVersionPath);
  if (!version) {
    VLOG(1) << "User model schema version is missing";
    return;
  }

  if (kCurrentSchemaVersion != *version) {
    VLOG(1) << "User model schema version mismatch";
    return;
  }

  const base::Value* user_model_values = manifest->FindListPath(kModelsPath);
  if (!user_model_values) {
    VLOG(1) << "No user models found";
    return;
  }

  for (const auto& user_model_value : user_model_values->GetList()) {
    UserModelInfo user_model;

    const std::string* id = user_model_value.FindStringPath(kModelsIdPath);
    if (!id) {
      VLOG(1) << *id << " user model id is missing";
      continue;
    }
    user_model.id = *id;

    const base::Optional<int> version =
        user_model_value.FindIntPath(kModelsVersionPath);
    if (!version) {
      VLOG(1) << *id << " user model version is missing";
      continue;
    }
    user_model.version = *version;

    const std::string* path =
        user_model_value.FindStringPath(kModelsFilenamePath);
    if (!path) {
      VLOG(1) << *id << " user model path is missing";
      continue;
    }
    user_model.path = install_dir.AppendASCII(*path);

    auto iter = user_models_.find(user_model.id);
    if (iter != user_models_.end()) {
      VLOG(1) << "Updating " << user_model.id << " user model";
      iter->second = user_model;
    } else {
      VLOG(1) << "Adding " << user_model.id << " user model";
      user_models_.insert({user_model.id, user_model});
    }

    VLOG(1) << "Notifying user model observers";
    NotifyObservers(user_model.id);
  }
}

void UserModelFileService::NotifyObservers(
    const std::string& id) {
  for (auto& observer : observers_) {
    observer.OnUserModelUpdated(id);
  }
}

void UserModelFileService::AddObserver(
    Observer* observer) {
  DCHECK(observer);

  observers_.AddObserver(observer);
}

void UserModelFileService::RemoveObserver(
    Observer* observer) {
  DCHECK(observer);

  observers_.RemoveObserver(observer);
}

base::Optional<base::FilePath> UserModelFileService::GetPath(
    const std::string& id) {
  const auto iter = user_models_.find(id);
  if (iter == user_models_.end()) {
    return base::nullopt;
  }

  const UserModelInfo user_model = iter->second;
  return user_model.path;
}

}  // namespace brave_user_model

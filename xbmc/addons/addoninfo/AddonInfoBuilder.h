/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "addons/Repository.h"

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class TiXmlElement;

namespace ADDON
{

class CAddonInfoBuilder
{
public:
  static AddonInfoPtr Generate(const std::string& id, TYPE type);
  static AddonInfoPtr Generate(const std::string& addonPath, bool platformCheck = true);
  static AddonInfoPtr Generate(const TiXmlElement* baseElement, const CRepository::DirInfo& repo, bool platformCheck = true);

  class CFromDB
  {
  public:
    CFromDB();

    void SetId(std::string id);
    void SetName(std::string name);
    void SetLicense(std::string license);
    void SetSummary(std::string summary);
    void SetDescription(std::string description);
    void SetDisclaimer(std::string disclaimer);
    void SetAuthor(std::string author);
    void SetSource(std::string source);
    void SetWebsite(std::string website);
    void SetForum(std::string forum);
    void SetEMail(std::string email);
    void SetIcon(std::string icon);
    void SetArt(const std::string& type, std::string value);
    void SetArt(std::map<std::string, std::string> art);
    void SetScreenshots(std::vector<std::string> screenshots);
    void SetChangelog(std::string changelog);
    void SetLifecycleState(AddonLifecycleState state, std::string description);
    void SetPath(std::string path);
    void SetLibName(std::string libname);
    void SetVersion(AddonVersion version);
    void SetDependencies(std::vector<DependencyInfo> dependencies);
    void SetExtrainfo(InfoMap extrainfo);
    void SetInstallDate(const CDateTime& installDate);
    void SetLastUpdated(const CDateTime& lastUpdated);
    void SetLastUsed(const CDateTime& lastUsed);
    void SetOrigin(std::string origin);
    void SetPackageSize(uint64_t size);
    void SetExtensions(CAddonType addonType);

    const AddonInfoPtr& get() { return m_addonInfo; }

  private:
    AddonInfoPtr m_addonInfo;
  };

  /*!
    * @brief Parts used from CAddonDatabase
    */
  //@{
  static void SetInstallData(const AddonInfoPtr& addon, const CDateTime& installDate,
                             const CDateTime& lastUpdated, const CDateTime& lastUsed, const std::string& origin);
  //@}

private:
  static bool ParseXML(const AddonInfoPtr& addon, const TiXmlElement* element, const std::string& addonPath, const CRepository::DirInfo& repo = {});
  static bool ParseXMLTypes(CAddonType& addonType,
                            const AddonInfoPtr& info,
                            const TiXmlElement* child);
  static bool ParseXMLExtension(CAddonExtensions& addonExt, const TiXmlElement* element);
  static bool GetTextList(const TiXmlElement* element, const std::string& tag, std::unordered_map<std::string, std::string>& translatedValues);
  static const char* GetPlatformLibraryName(const TiXmlElement* element);
  static bool PlatformSupportsAddon(const AddonInfoPtr& addon);
};

}

/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/toolbar/brave_bookmark_sub_menu_model.h"
#include "brave/browser/ui/toolbar/brave_recent_tabs_sub_menu_model.h"
#include "chrome/browser/ui/toolbar/bookmark_sub_menu_model.h"

#define RecentTabsSubMenuModel BraveRecentTabsSubMenuModel
#define BookmarkSubMenuModel BraveBookmarkSubMenuModel
#include "src/chrome/browser/ui/toolbar/app_menu_model.cc"
#undef BookmarkSubMenuModel
#undef RecentTabsSubMenuModel

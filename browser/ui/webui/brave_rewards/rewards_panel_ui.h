/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_UI_WEBUI_BRAVE_REWARDS_REWARDS_PANEL_UI_H_
#define BRAVE_BROWSER_UI_WEBUI_BRAVE_REWARDS_REWARDS_PANEL_UI_H_

#include <memory>

#include "base/memory/raw_ptr.h"
#include "brave/components/brave_rewards/common/brave_rewards_panel.mojom.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "ui/webui/mojo_bubble_web_ui_controller.h"

class Browser;

namespace brave_rewards {
class RewardsPanelCoordinator;
}

class RewardsPanelUI : public ui::MojoBubbleWebUIController,
                       public brave_rewards::mojom::PanelHandlerFactory {
 public:
  explicit RewardsPanelUI(content::WebUI* web_ui);
  ~RewardsPanelUI() override;

  RewardsPanelUI(const RewardsPanelUI&) = delete;
  RewardsPanelUI& operator=(const RewardsPanelUI&) = delete;

  void BindInterface(mojo::PendingReceiver<PanelHandlerFactory> receiver);

 private:
  // brave_rewards::mojom::PanelHandlerFactory:
  void CreatePanelHandler(
      mojo::PendingRemote<brave_rewards::mojom::Panel> panel,
      mojo::PendingReceiver<brave_rewards::mojom::PanelHandler> receiver)
      override;

  std::unique_ptr<brave_rewards::mojom::PanelHandler> panel_handler_;
  mojo::Receiver<PanelHandlerFactory> panel_factory_receiver_{this};
  raw_ptr<brave_rewards::RewardsPanelCoordinator> panel_coordinator_ = nullptr;

  WEB_UI_CONTROLLER_TYPE_DECL();
};

#endif  // BRAVE_BROWSER_UI_WEBUI_BRAVE_REWARDS_REWARDS_PANEL_UI_H_

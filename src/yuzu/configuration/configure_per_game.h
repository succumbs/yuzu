﻿// SPDX-FileCopyrightText: Copyright 2020 yuzu Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <forward_list>
#include <memory>
#include <string>
#include <vector>

#include <QDialog>
#include <QList>

#include "configuration/shared_widget.h"
#include "core/file_sys/vfs_types.h"
#include "vk_device_info.h"
#include "yuzu/configuration/config.h"
#include "yuzu/configuration/configuration_shared.h"
#include "yuzu/configuration/shared_translation.h"

namespace Core {
class System;
}

namespace InputCommon {
class InputSubsystem;
}

class ConfigurePerGameAddons;
class ConfigureAudio;
class ConfigureCpu;
class ConfigureGraphics;
class ConfigureGraphicsAdvanced;
class ConfigureInputPerGame;
class ConfigureSystem;

class QGraphicsScene;
class QStandardItem;
class QStandardItemModel;
class QTreeView;
class QVBoxLayout;

namespace Ui {
class ConfigurePerGame;
}

class ConfigurePerGame : public QDialog {
    Q_OBJECT

public:
    // Cannot use std::filesystem::path due to https://bugreports.qt.io/browse/QTBUG-73263
    explicit ConfigurePerGame(QWidget* parent, u64 title_id_, const std::string& file_name,
                              std::vector<VkDeviceInfo::Record>& vk_device_records,
                              Core::System& system_);
    ~ConfigurePerGame() override;

    /// Save all button configurations to settings file
    void ApplyConfiguration();

    void LoadFromFile(FileSys::VirtualFile file_);

private:
    void changeEvent(QEvent* event) override;
    void RetranslateUI();

    void HandleApplyButtonClicked();

    void LoadConfiguration();

    std::unique_ptr<Ui::ConfigurePerGame> ui;
    FileSys::VirtualFile file;
    u64 title_id;

    QGraphicsScene* scene;

    std::unique_ptr<Config> game_config;

    Core::System& system;
    std::unique_ptr<ConfigurationShared::Builder> builder;
    std::shared_ptr<std::forward_list<ConfigurationShared::Tab*>> tab_group;

    std::unique_ptr<ConfigurePerGameAddons> addons_tab;
    std::unique_ptr<ConfigureAudio> audio_tab;
    std::unique_ptr<ConfigureCpu> cpu_tab;
    std::unique_ptr<ConfigureGraphicsAdvanced> graphics_advanced_tab;
    std::unique_ptr<ConfigureGraphics> graphics_tab;
    std::unique_ptr<ConfigureInputPerGame> input_tab;
    std::unique_ptr<ConfigureSystem> system_tab;
};

#include "displayapp/screens/settings/Settings.h"
#include <lvgl/lvgl.h>
#include <array>
#include "displayapp/screens/List.h"
#include "displayapp/Apps.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"

using namespace Pinetime::Applications::Screens;

Settings::Settings(Pinetime::Applications::DisplayApp* app, Pinetime::Controllers::Settings& settingsController)
  : Screen(app),
    settingsController {settingsController},
    screens {app,
             settingsController.GetSettingsMenu(),
             {[this]() -> std::unique_ptr<Screen> {
                return CreateScreen1();
              },
              [this]() -> std::unique_ptr<Screen> {
                return CreateScreen2();
              },
              [this]() -> std::unique_ptr<Screen> {
                return CreateScreen3();
              }},
             Screens::ScreenListModes::UpDown} {
}

Settings::~Settings() {
  lv_obj_clean(lv_scr_act());
}

bool Settings::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  return screens.OnTouchEvent(event);
}

std::unique_ptr<Screen> Settings::CreateScreen1() {

  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::sun, "Affichage", Apps::SettingDisplay},
    {Symbols::eye, "Reveille", Apps::SettingWakeUp},
    {Symbols::clock, "Format de l'hrs", Apps::SettingTimeFormat},
    {Symbols::home, "Cadran", Apps::SettingWatchFace},
  }};

  return std::make_unique<Screens::List>(0, 3, app, settingsController, applications);
}

std::unique_ptr<Screen> Settings::CreateScreen2() {

  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::shoe, "Pas", Apps::SettingSteps},
    {Symbols::clock, "Editer la date", Apps::SettingSetDate},
    {Symbols::clock, "Editer l'heure", Apps::SettingSetTime},
    {Symbols::batteryHalf, "Batterie", Apps::BatteryInfo}
  }};

  return std::make_unique<Screens::List>(1, 3, app, settingsController, applications);
}

std::unique_ptr<Screen> Settings::CreateScreen3() {

  std::array<Screens::List::Applications, 4> applications {{
    {Symbols::paintbrush, "PTS Couleurs", Apps::SettingPineTimeStyle},
    {Symbols::check, "Firmware", Apps::FirmwareValidation},
    {Symbols::list, "About", Apps::SysInfo},
    {Symbols::none, "None", Apps::None},
  }};

  return std::make_unique<Screens::List>(2, 3, app, settingsController, applications);
}

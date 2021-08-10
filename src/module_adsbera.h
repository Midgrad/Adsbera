#ifndef MODULE_ADSBERA_H
#define MODULE_ADSBERA_H

#include "i_module.h"

namespace adsbera::app
{
class ModuleAdsbera
    : public QObject
    , public kjarni::app::IModule
{
    Q_OBJECT
    Q_INTERFACES(kjarni::app::IModule)
    Q_PLUGIN_METADATA(IID "Midgrad.ModuleAdsb" FILE "meta.json")

public:
    Q_INVOKABLE ModuleAdsbera();

    void init() override;
    void done() override;

    QJsonObject qmlEntries() const override;
};
} // namespace adsbera::app

#endif // MODULE_ADSBERA_H

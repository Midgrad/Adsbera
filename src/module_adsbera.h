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
    Q_PLUGIN_METADATA(IID "Midgrad.ModuleAdsbera" FILE "meta.json")

public:
    Q_INVOKABLE ModuleAdsbera();

    void visit(QJsonObject& features) override;
};
} // namespace adsbera::app

#endif // MODULE_ADSBERA_H

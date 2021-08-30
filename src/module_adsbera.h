#ifndef MODULE_ADSBERA_H
#define MODULE_ADSBERA_H

#include "i_module.h"

namespace md::app
{
class ModuleAdsbera
    : public QObject
    , public md::app::IModule
{
    Q_OBJECT
    Q_INTERFACES(md::app::IModule)
    Q_PLUGIN_METADATA(IID "Midgrad.ModuleAdsbera" FILE "meta.json")

public:
    Q_INVOKABLE ModuleAdsbera();

    void visit(QJsonObject& features) override;
};
} // namespace adsbera::app

#endif // MODULE_ADSBERA_H

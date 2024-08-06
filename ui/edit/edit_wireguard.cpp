#include "edit_wireguard.h"
#include "ui_edit_wireguard.h"

#include "fmt/WireguardBean.h"

EditWireguard::EditWireguard(QWidget *parent) : QWidget(parent), ui(new Ui::EditWireguard) {
    ui->setupUi(this);
}

EditWireguard::~EditWireguard() {
    delete ui;
}

void EditWireguard::onStart(std::shared_ptr<NekoGui::ProxyEntity> _ent) {
    this->ent = _ent;
    auto bean = this->ent->WireguardBean();

#ifndef Q_OS_LINUX
    ui->enable_gso->hide();
    adjustSize();
#endif

    ui->private_key->setText(bean->privateKey);
    ui->public_key->setText(bean->publicKey);
    ui->preshared_key->setText(bean->preSharedKey);
    auto reservedStr = bean->FormatReserved().replace("-", ",");
    ui->reserved->setText(reservedStr);
    ui->mtu->setText(Int2String(bean->MTU));
    ui->sys_ifc->setChecked(bean->useSystemInterface);
    ui->enable_gso->setChecked(bean->enableGSO);
}

bool EditWireguard::onEnd() {
    auto bean = this->ent->WireguardBean();

    bean->privateKey = ui->private_key->text();
    bean->publicKey = ui->public_key->text();
    bean->preSharedKey = ui->preshared_key->text();
    auto rawReserved = ui->reserved->text();
    bean->reserved = {};
    for (const auto& item: rawReserved.split(",")) {
        bean->reserved += item.trimmed().toInt();
    }
    bean->MTU = ui->mtu->text().toInt();
    bean->useSystemInterface = ui->sys_ifc->isChecked();
    bean->enableGSO = ui->enable_gso->isChecked();

    return true;
}
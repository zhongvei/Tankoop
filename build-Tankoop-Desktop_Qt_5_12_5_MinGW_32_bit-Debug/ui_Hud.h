/********************************************************************************
** Form generated from reading UI file 'Hud.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUD_H
#define UI_HUD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hud
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *max_health_layout;
    QLabel *max_health_label;
    QLabel *max_health_value;
    QPushButton *increase_max_health_btn;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *health_regen_layout;
    QLabel *health_regen_label;
    QLabel *health_regen_value;
    QPushButton *increase_health_regen_btn;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *damage_layout;
    QLabel *damage_label;
    QLabel *damage_value;
    QPushButton *increase_damage_btn;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *movement_speed_layout;
    QLabel *movement_speed_label;
    QLabel *movement_speed_value;
    QPushButton *increase_movement_speed_btn;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *attack_speed_layout;
    QLabel *attack_speed_label;
    QLabel *attack_speed_value;
    QPushButton *increase_attack_speed_btn;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *bullet_speed_layout;
    QLabel *bullet_speed_label;
    QLabel *bullet_speed_value;
    QPushButton *increase_bullet_speed_btn;
    QWidget *horizontalLayoutWidget_9;
    QHBoxLayout *level_exp_layout;
    QHBoxLayout *exp_layout;
    QLabel *exp_label;
    QLabel *exp_value;
    QHBoxLayout *level_layout;
    QLabel *level_label;
    QLabel *level_value;
    QLabel *skill_point_value;
    QLabel *skill_point_label;
    QFrame *line;

    void setupUi(QWidget *Hud)
    {
        if (Hud->objectName().isEmpty())
            Hud->setObjectName(QString::fromUtf8("Hud"));
        Hud->setEnabled(true);
        Hud->resize(224, 389);
        QFont font;
        font.setFamily(QString::fromUtf8("MV Boli"));
        Hud->setFont(font);
        Hud->setWindowOpacity(0.500000000000000);
        Hud->setAutoFillBackground(true);
        horizontalLayoutWidget = new QWidget(Hud);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 201, 26));
        max_health_layout = new QHBoxLayout(horizontalLayoutWidget);
        max_health_layout->setObjectName(QString::fromUtf8("max_health_layout"));
        max_health_layout->setContentsMargins(0, 0, 0, 0);
        max_health_label = new QLabel(horizontalLayoutWidget);
        max_health_label->setObjectName(QString::fromUtf8("max_health_label"));

        max_health_layout->addWidget(max_health_label);

        max_health_value = new QLabel(horizontalLayoutWidget);
        max_health_value->setObjectName(QString::fromUtf8("max_health_value"));

        max_health_layout->addWidget(max_health_value);

        increase_max_health_btn = new QPushButton(horizontalLayoutWidget);
        increase_max_health_btn->setObjectName(QString::fromUtf8("increase_max_health_btn"));

        max_health_layout->addWidget(increase_max_health_btn);

        horizontalLayoutWidget_2 = new QWidget(Hud);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 50, 201, 26));
        health_regen_layout = new QHBoxLayout(horizontalLayoutWidget_2);
        health_regen_layout->setObjectName(QString::fromUtf8("health_regen_layout"));
        health_regen_layout->setContentsMargins(0, 0, 0, 0);
        health_regen_label = new QLabel(horizontalLayoutWidget_2);
        health_regen_label->setObjectName(QString::fromUtf8("health_regen_label"));

        health_regen_layout->addWidget(health_regen_label);

        health_regen_value = new QLabel(horizontalLayoutWidget_2);
        health_regen_value->setObjectName(QString::fromUtf8("health_regen_value"));

        health_regen_layout->addWidget(health_regen_value);

        increase_health_regen_btn = new QPushButton(horizontalLayoutWidget_2);
        increase_health_regen_btn->setObjectName(QString::fromUtf8("increase_health_regen_btn"));

        health_regen_layout->addWidget(increase_health_regen_btn);

        horizontalLayoutWidget_3 = new QWidget(Hud);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 90, 201, 26));
        damage_layout = new QHBoxLayout(horizontalLayoutWidget_3);
        damage_layout->setObjectName(QString::fromUtf8("damage_layout"));
        damage_layout->setContentsMargins(0, 0, 0, 0);
        damage_label = new QLabel(horizontalLayoutWidget_3);
        damage_label->setObjectName(QString::fromUtf8("damage_label"));

        damage_layout->addWidget(damage_label);

        damage_value = new QLabel(horizontalLayoutWidget_3);
        damage_value->setObjectName(QString::fromUtf8("damage_value"));

        damage_layout->addWidget(damage_value);

        increase_damage_btn = new QPushButton(horizontalLayoutWidget_3);
        increase_damage_btn->setObjectName(QString::fromUtf8("increase_damage_btn"));

        damage_layout->addWidget(increase_damage_btn);

        horizontalLayoutWidget_4 = new QWidget(Hud);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 130, 201, 26));
        movement_speed_layout = new QHBoxLayout(horizontalLayoutWidget_4);
        movement_speed_layout->setObjectName(QString::fromUtf8("movement_speed_layout"));
        movement_speed_layout->setContentsMargins(0, 0, 0, 0);
        movement_speed_label = new QLabel(horizontalLayoutWidget_4);
        movement_speed_label->setObjectName(QString::fromUtf8("movement_speed_label"));

        movement_speed_layout->addWidget(movement_speed_label);

        movement_speed_value = new QLabel(horizontalLayoutWidget_4);
        movement_speed_value->setObjectName(QString::fromUtf8("movement_speed_value"));

        movement_speed_layout->addWidget(movement_speed_value);

        increase_movement_speed_btn = new QPushButton(horizontalLayoutWidget_4);
        increase_movement_speed_btn->setObjectName(QString::fromUtf8("increase_movement_speed_btn"));

        movement_speed_layout->addWidget(increase_movement_speed_btn);

        horizontalLayoutWidget_5 = new QWidget(Hud);
        horizontalLayoutWidget_5->setObjectName(QString::fromUtf8("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 170, 201, 26));
        attack_speed_layout = new QHBoxLayout(horizontalLayoutWidget_5);
        attack_speed_layout->setObjectName(QString::fromUtf8("attack_speed_layout"));
        attack_speed_layout->setContentsMargins(0, 0, 0, 0);
        attack_speed_label = new QLabel(horizontalLayoutWidget_5);
        attack_speed_label->setObjectName(QString::fromUtf8("attack_speed_label"));

        attack_speed_layout->addWidget(attack_speed_label);

        attack_speed_value = new QLabel(horizontalLayoutWidget_5);
        attack_speed_value->setObjectName(QString::fromUtf8("attack_speed_value"));

        attack_speed_layout->addWidget(attack_speed_value);

        increase_attack_speed_btn = new QPushButton(horizontalLayoutWidget_5);
        increase_attack_speed_btn->setObjectName(QString::fromUtf8("increase_attack_speed_btn"));

        attack_speed_layout->addWidget(increase_attack_speed_btn);

        horizontalLayoutWidget_6 = new QWidget(Hud);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(10, 210, 201, 26));
        bullet_speed_layout = new QHBoxLayout(horizontalLayoutWidget_6);
        bullet_speed_layout->setObjectName(QString::fromUtf8("bullet_speed_layout"));
        bullet_speed_layout->setContentsMargins(0, 0, 0, 0);
        bullet_speed_label = new QLabel(horizontalLayoutWidget_6);
        bullet_speed_label->setObjectName(QString::fromUtf8("bullet_speed_label"));

        bullet_speed_layout->addWidget(bullet_speed_label);

        bullet_speed_value = new QLabel(horizontalLayoutWidget_6);
        bullet_speed_value->setObjectName(QString::fromUtf8("bullet_speed_value"));

        bullet_speed_layout->addWidget(bullet_speed_value);

        increase_bullet_speed_btn = new QPushButton(horizontalLayoutWidget_6);
        increase_bullet_speed_btn->setObjectName(QString::fromUtf8("increase_bullet_speed_btn"));

        bullet_speed_layout->addWidget(increase_bullet_speed_btn);

        horizontalLayoutWidget_9 = new QWidget(Hud);
        horizontalLayoutWidget_9->setObjectName(QString::fromUtf8("horizontalLayoutWidget_9"));
        horizontalLayoutWidget_9->setGeometry(QRect(10, 270, 201, 25));
        level_exp_layout = new QHBoxLayout(horizontalLayoutWidget_9);
        level_exp_layout->setObjectName(QString::fromUtf8("level_exp_layout"));
        level_exp_layout->setContentsMargins(0, 0, 0, 0);
        exp_layout = new QHBoxLayout();
        exp_layout->setObjectName(QString::fromUtf8("exp_layout"));
        exp_label = new QLabel(horizontalLayoutWidget_9);
        exp_label->setObjectName(QString::fromUtf8("exp_label"));

        exp_layout->addWidget(exp_label);

        exp_value = new QLabel(horizontalLayoutWidget_9);
        exp_value->setObjectName(QString::fromUtf8("exp_value"));

        exp_layout->addWidget(exp_value);


        level_exp_layout->addLayout(exp_layout);

        level_layout = new QHBoxLayout();
        level_layout->setObjectName(QString::fromUtf8("level_layout"));
        level_label = new QLabel(horizontalLayoutWidget_9);
        level_label->setObjectName(QString::fromUtf8("level_label"));

        level_layout->addWidget(level_label);

        level_value = new QLabel(horizontalLayoutWidget_9);
        level_value->setObjectName(QString::fromUtf8("level_value"));

        level_layout->addWidget(level_value);


        level_exp_layout->addLayout(level_layout);

        skill_point_value = new QLabel(Hud);
        skill_point_value->setObjectName(QString::fromUtf8("skill_point_value"));
        skill_point_value->setGeometry(QRect(110, 310, 95, 17));
        skill_point_label = new QLabel(Hud);
        skill_point_label->setObjectName(QString::fromUtf8("skill_point_label"));
        skill_point_label->setGeometry(QRect(10, 310, 96, 17));
        line = new QFrame(Hud);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 250, 231, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(Hud);

        QMetaObject::connectSlotsByName(Hud);
    } // setupUi

    void retranslateUi(QWidget *Hud)
    {
        Hud->setWindowTitle(QApplication::translate("Hud", "Form", nullptr));
        max_health_label->setText(QApplication::translate("Hud", "Max Health:", nullptr));
        max_health_value->setText(QApplication::translate("Hud", "0", nullptr));
        increase_max_health_btn->setText(QApplication::translate("Hud", "+", nullptr));
        health_regen_label->setText(QApplication::translate("Hud", "Health Regen:", nullptr));
        health_regen_value->setText(QApplication::translate("Hud", "0", nullptr));
        increase_health_regen_btn->setText(QApplication::translate("Hud", "+", nullptr));
        damage_label->setText(QApplication::translate("Hud", "Damage:", nullptr));
        damage_value->setText(QApplication::translate("Hud", "0", nullptr));
        increase_damage_btn->setText(QApplication::translate("Hud", "+", nullptr));
        movement_speed_label->setText(QApplication::translate("Hud", "Movement Speed:", nullptr));
        movement_speed_value->setText(QApplication::translate("Hud", "0", nullptr));
        increase_movement_speed_btn->setText(QApplication::translate("Hud", "+", nullptr));
        attack_speed_label->setText(QApplication::translate("Hud", "Attack Speed:", nullptr));
        attack_speed_value->setText(QApplication::translate("Hud", "0", nullptr));
        increase_attack_speed_btn->setText(QApplication::translate("Hud", "+", nullptr));
        bullet_speed_label->setText(QApplication::translate("Hud", "Bullet Speed:", nullptr));
        bullet_speed_value->setText(QApplication::translate("Hud", "0", nullptr));
        increase_bullet_speed_btn->setText(QApplication::translate("Hud", "+", nullptr));
        exp_label->setText(QApplication::translate("Hud", "Exp:", nullptr));
        exp_value->setText(QApplication::translate("Hud", "0", nullptr));
        level_label->setText(QApplication::translate("Hud", "Level:", nullptr));
        level_value->setText(QApplication::translate("Hud", "0", nullptr));
        skill_point_value->setText(QApplication::translate("Hud", "0", nullptr));
        skill_point_label->setText(QApplication::translate("Hud", "Upgrade Available:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hud: public Ui_Hud {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUD_H

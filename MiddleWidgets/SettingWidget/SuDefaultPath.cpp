﻿#include <global.h>
#include "SuDefaultPath.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include "BesMessageBox.h"
#include "BesScaleUtil.h"

QString SuDefaultPath::getName()
{
   return tr("默认路径");
}

int SuDefaultPath::getUnitHeight()
{
   return 260* BesScaleUtil::mscale();
}

QWidget *SuDefaultPath::getUnitWidget(QWidget *parent)
{
    SettingUnitContainer = new QWidget(parent);
    SettingUnitContainer->setObjectName("SettingUnitContainer");

    labelSettingTitle = new QLabel(SettingUnitContainer);
    labelSettingTitle->setObjectName("settingUnitTitle");
    labelSettingTitle->setText(tr("默认路径"));

    QHBoxLayout* hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(labelSettingTitle);
    hLayout1->addSpacerItem(new QSpacerItem(20* BesScaleUtil::mscale(),20,QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    btnSelectDefaultPathMusic  = new BesButton(SettingUnitContainer);
    btnSelectDefaultPathLyric  = new BesButton(SettingUnitContainer);
    btnSelectDefaultPathOutput = new BesButton(SettingUnitContainer);
    labelTipPathMusic  = new QLabel(SettingUnitContainer);
    labelTipPathLyric  = new QLabel(SettingUnitContainer);
    labelTipPathOutput = new QLabel(SettingUnitContainer);
    labelDefaultPathMusic = new QLabel(SettingUnitContainer);
    labelDefaultPathLyric = new QLabel(SettingUnitContainer);
    labelDefaultPathOutput= new QLabel(SettingUnitContainer);

    btnSelectDefaultPathMusic->setText(tr("选择"));
    btnSelectDefaultPathLyric->setText(tr("选择"));
    btnSelectDefaultPathOutput->setText(tr("选择"));
    btnSelectDefaultPathMusic->setMinimumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    btnSelectDefaultPathMusic->setMaximumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    btnSelectDefaultPathLyric->setMinimumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    btnSelectDefaultPathLyric->setMaximumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    btnSelectDefaultPathOutput->setMinimumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    btnSelectDefaultPathOutput->setMaximumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    btnSelectDefaultPathMusic->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btnSelectDefaultPathLyric->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btnSelectDefaultPathOutput->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    labelTipPathMusic->setText(tr("音乐目录："));
    labelTipPathLyric->setText(tr("歌词目录："));
    labelTipPathOutput->setText(tr("输出目录："));
    labelTipPathMusic->setMinimumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    labelTipPathMusic->setMaximumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    labelTipPathLyric->setMinimumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    labelTipPathLyric->setMaximumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    labelTipPathOutput->setMinimumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    labelTipPathOutput->setMaximumSize(80* BesScaleUtil::mscale(),30* BesScaleUtil::mscale());
    labelTipPathMusic->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelTipPathLyric->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    labelTipPathOutput->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    labelDefaultPathMusic->setMinimumHeight(30* BesScaleUtil::mscale());
    labelDefaultPathMusic->setMaximumHeight(30* BesScaleUtil::mscale());
    labelDefaultPathLyric->setMinimumHeight(30* BesScaleUtil::mscale());
    labelDefaultPathLyric->setMaximumHeight(30* BesScaleUtil::mscale());
    labelDefaultPathOutput->setMinimumHeight(30* BesScaleUtil::mscale());
    labelDefaultPathOutput->setMaximumHeight(30* BesScaleUtil::mscale());
    labelDefaultPathMusic->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    labelDefaultPathLyric->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    labelDefaultPathOutput->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(btnSelectDefaultPathMusic);
    hLayout2->addWidget(labelTipPathMusic);
    hLayout2->addWidget(labelDefaultPathMusic);

    QHBoxLayout* hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(btnSelectDefaultPathLyric);
    hLayout3->addWidget(labelTipPathLyric);
    hLayout3->addWidget(labelDefaultPathLyric);

    QHBoxLayout* hLayout4 = new QHBoxLayout();
    hLayout4->addWidget(btnSelectDefaultPathOutput);
    hLayout4->addWidget(labelTipPathOutput);
    hLayout4->addWidget(labelDefaultPathOutput);

    QVBoxLayout* vLayout = new QVBoxLayout(SettingUnitContainer);
    vLayout->setSpacing(15* BesScaleUtil::mscale());
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);
    vLayout->addLayout(hLayout4);
    vLayout->addSpacerItem(new QSpacerItem(20,20* BesScaleUtil::mscale(), QSizePolicy::Fixed ,QSizePolicy::MinimumExpanding));


    labelDefaultPathMusic->setText(SettingManager::GetInstance().data().defaultMusicPath);
    labelDefaultPathLyric->setText(SettingManager::GetInstance().data().defaultLyricPath);
    labelDefaultPathOutput->setText(SettingManager::GetInstance().data().defaultOutputPath);

    //连接信号

    connect(btnSelectDefaultPathMusic, &QPushButton::clicked, [=]()
    {
        QString backup = SettingManager::GetInstance().data().defaultMusicPath;
        QString dir = QFileDialog::getExistingDirectory(parent, tr("选择默认歌曲目录"),  backup,
                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if(dir.size() !=0)
        {
            labelDefaultPathMusic->setText(dir);

            SettingManager::GetInstance().data().defaultMusicPath = dir;

            if(!SettingManager::GetInstance().saveSettingData())
            {
                SettingManager::GetInstance().data().defaultMusicPath = backup;
                labelDefaultPathMusic->setText(backup);
                BesMessageBox::information(tr("提示"),tr("保存失败，可能是程序没有写权限"));
            }
        }
    });

    connect(btnSelectDefaultPathLyric, &QPushButton::clicked, [=]()
    {
        QString backup = SettingManager::GetInstance().data().defaultLyricPath;
        QString dir = QFileDialog::getExistingDirectory(parent, tr("选择默认歌词目录"),  backup,
                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if(dir.size() !=0)
        {
            labelDefaultPathLyric->setText(dir);

            SettingManager::GetInstance().data().defaultLyricPath = dir;

            if(!SettingManager::GetInstance().saveSettingData())
            {
                SettingManager::GetInstance().data().defaultLyricPath = backup;
                labelDefaultPathLyric->setText(backup);
                BesMessageBox::information(tr("提示"),tr("保存失败，可能是程序没有写权限"));
            }
        }
    });

    connect(btnSelectDefaultPathOutput, &QPushButton::clicked, [=]()
    {
        QString backup = SettingManager::GetInstance().data().defaultOutputPath;
        QString dir = QFileDialog::getExistingDirectory(parent, tr("选择默认输出目录"),  backup,
                                         QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if(dir.size() !=0)
        {
            labelDefaultPathOutput->setText(dir);

            SettingManager::GetInstance().data().defaultOutputPath = dir;

            if(!SettingManager::GetInstance().saveSettingData())
            {
                SettingManager::GetInstance().data().defaultOutputPath = backup;
                labelDefaultPathOutput->setText(backup);
                BesMessageBox::information(tr("提示"),tr("保存失败，可能是程序没有写权限"));
            }
        }
    });

    return SettingUnitContainer;
}

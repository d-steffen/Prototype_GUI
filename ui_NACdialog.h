/********************************************************************************
** Form generated from reading UI file 'NACdialog.ui'
**
** Created: Tue Jul 15 13:04:39 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NACDIALOG_H
#define UI_NACDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "TQtWidget.h"

QT_BEGIN_NAMESPACE

class Ui_UI_NACdialog
{
public:
    QAction *actionExit;
    QAction *actionSave_Log_File_as;
    QAction *action9_Channels;
    QAction *action1000_Channels;
    QAction *action1_Channel;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QWidget *leftSide;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *ControlBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *StartButton;
    QPushButton *ResetButton;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *SettingsBox;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *NumberLabel;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_6;
    QSpinBox *NumberSpinBox;
    QSpacerItem *horizontalSpacer_9;
    QLabel *ConsecutiveLabel;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    QSpinBox *ConsecutiveSpinBox;
    QSpacerItem *horizontalSpacer_10;
    QLabel *MultiplicationLabel;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_8;
    QSpinBox *FactorSpinBox;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *ApplyButton;
    QTextBrowser *Console;
    QGroupBox *DisplayBox;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_2;
    QProgressBar *progressBarReads;
    QLabel *ReadsLabel;
    QProgressBar *progressBarBuffer;
    QLabel *BufferLabel;
    QSpacerItem *horizontalSpacer_5;
    QProgressBar *progressBarData;
    QLabel *DataLabel;
    QSpacerItem *horizontalSpacer_4;
    QProgressBar *progressBarPCBuffer;
    QLabel *PCBufferLabel;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QComboBox *ComboBox;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_9;
    TQtWidget *CanvasScope;
    TQtWidget *CanvasSpectrum;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_13;
    TQtWidget *CanvasHeatMap;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuChannel_conf;

    void setupUi(QMainWindow *UI_NACdialog)
    {
        if (UI_NACdialog->objectName().isEmpty())
            UI_NACdialog->setObjectName(QString::fromUtf8("UI_NACdialog"));
        UI_NACdialog->setEnabled(true);
        UI_NACdialog->resize(1160, 875);
        UI_NACdialog->setMinimumSize(QSize(400, 0));
        actionExit = new QAction(UI_NACdialog);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSave_Log_File_as = new QAction(UI_NACdialog);
        actionSave_Log_File_as->setObjectName(QString::fromUtf8("actionSave_Log_File_as"));
        action9_Channels = new QAction(UI_NACdialog);
        action9_Channels->setObjectName(QString::fromUtf8("action9_Channels"));
        action1000_Channels = new QAction(UI_NACdialog);
        action1000_Channels->setObjectName(QString::fromUtf8("action1000_Channels"));
        action1_Channel = new QAction(UI_NACdialog);
        action1_Channel->setObjectName(QString::fromUtf8("action1_Channel"));
        centralwidget = new QWidget(UI_NACdialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftSide = new QWidget(centralwidget);
        leftSide->setObjectName(QString::fromUtf8("leftSide"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftSide->sizePolicy().hasHeightForWidth());
        leftSide->setSizePolicy(sizePolicy);
        leftSide->setMinimumSize(QSize(400, 0));
        leftSide->setMaximumSize(QSize(400, 16777215));
        verticalLayout_3 = new QVBoxLayout(leftSide);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        ControlBox = new QGroupBox(leftSide);
        ControlBox->setObjectName(QString::fromUtf8("ControlBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ControlBox->sizePolicy().hasHeightForWidth());
        ControlBox->setSizePolicy(sizePolicy1);
        ControlBox->setMinimumSize(QSize(0, 100));
        horizontalLayout = new QHBoxLayout(ControlBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(215, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        StartButton = new QPushButton(ControlBox);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy2);
        StartButton->setMinimumSize(QSize(150, 0));
        StartButton->setContextMenuPolicy(Qt::NoContextMenu);
        StartButton->setCheckable(true);
        StartButton->setChecked(false);

        verticalLayout->addWidget(StartButton);

        ResetButton = new QPushButton(ControlBox);
        ResetButton->setObjectName(QString::fromUtf8("ResetButton"));
        ResetButton->setEnabled(true);
        ResetButton->setCheckable(true);

        verticalLayout->addWidget(ResetButton);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(215, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addWidget(ControlBox);

        SettingsBox = new QGroupBox(leftSide);
        SettingsBox->setObjectName(QString::fromUtf8("SettingsBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(SettingsBox->sizePolicy().hasHeightForWidth());
        SettingsBox->setSizePolicy(sizePolicy3);
        SettingsBox->setMinimumSize(QSize(388, 130));
        verticalLayout_2 = new QVBoxLayout(SettingsBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        NumberLabel = new QLabel(SettingsBox);
        NumberLabel->setObjectName(QString::fromUtf8("NumberLabel"));

        gridLayout->addWidget(NumberLabel, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        NumberSpinBox = new QSpinBox(SettingsBox);
        NumberSpinBox->setObjectName(QString::fromUtf8("NumberSpinBox"));
        NumberSpinBox->setFrame(true);
        NumberSpinBox->setMinimum(2);
        NumberSpinBox->setMaximum(256);
        NumberSpinBox->setSingleStep(2);
        NumberSpinBox->setValue(50);

        horizontalLayout_6->addWidget(NumberSpinBox);

        horizontalSpacer_9 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        gridLayout->addLayout(horizontalLayout_6, 0, 1, 1, 1);

        ConsecutiveLabel = new QLabel(SettingsBox);
        ConsecutiveLabel->setObjectName(QString::fromUtf8("ConsecutiveLabel"));

        gridLayout->addWidget(ConsecutiveLabel, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        ConsecutiveSpinBox = new QSpinBox(SettingsBox);
        ConsecutiveSpinBox->setObjectName(QString::fromUtf8("ConsecutiveSpinBox"));
        ConsecutiveSpinBox->setMinimum(1);
        ConsecutiveSpinBox->setMaximum(32);
        ConsecutiveSpinBox->setValue(2);

        horizontalLayout_7->addWidget(ConsecutiveSpinBox);

        horizontalSpacer_10 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_7, 1, 1, 1, 1);

        MultiplicationLabel = new QLabel(SettingsBox);
        MultiplicationLabel->setObjectName(QString::fromUtf8("MultiplicationLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(MultiplicationLabel->sizePolicy().hasHeightForWidth());
        MultiplicationLabel->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(MultiplicationLabel, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        FactorSpinBox = new QSpinBox(SettingsBox);
        FactorSpinBox->setObjectName(QString::fromUtf8("FactorSpinBox"));
        FactorSpinBox->setMinimum(1);
        FactorSpinBox->setMaximum(15);
        FactorSpinBox->setValue(4);

        horizontalLayout_8->addWidget(FactorSpinBox);

        horizontalSpacer_11 = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_11);


        gridLayout->addLayout(horizontalLayout_8, 2, 1, 1, 1);

        ApplyButton = new QPushButton(SettingsBox);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));
        sizePolicy2.setHeightForWidth(ApplyButton->sizePolicy().hasHeightForWidth());
        ApplyButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(ApplyButton, 3, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout_3->addWidget(SettingsBox);

        Console = new QTextBrowser(leftSide);
        Console->setObjectName(QString::fromUtf8("Console"));
        Console->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        Console->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        Console->setLineWrapMode(QTextEdit::WidgetWidth);
        Console->setSource(QUrl("file:///home/domi/FPGA_RO/GUI/log.txt"));
        Console->setOpenExternalLinks(false);
        Console->setOpenLinks(true);

        verticalLayout_3->addWidget(Console);


        horizontalLayout_2->addWidget(leftSide);

        DisplayBox = new QGroupBox(centralwidget);
        DisplayBox->setObjectName(QString::fromUtf8("DisplayBox"));
        verticalLayout_6 = new QVBoxLayout(DisplayBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        scrollArea = new QScrollArea(DisplayBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 691, 792));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        progressBarReads = new QProgressBar(scrollAreaWidgetContents);
        progressBarReads->setObjectName(QString::fromUtf8("progressBarReads"));
        sizePolicy2.setHeightForWidth(progressBarReads->sizePolicy().hasHeightForWidth());
        progressBarReads->setSizePolicy(sizePolicy2);
        progressBarReads->setMinimumSize(QSize(150, 0));
        progressBarReads->setMaximumSize(QSize(16777215, 20));
        progressBarReads->setMaximum(2500);
        progressBarReads->setValue(0);
        progressBarReads->setTextVisible(true);

        gridLayout_2->addWidget(progressBarReads, 0, 1, 1, 1);

        ReadsLabel = new QLabel(scrollAreaWidgetContents);
        ReadsLabel->setObjectName(QString::fromUtf8("ReadsLabel"));

        gridLayout_2->addWidget(ReadsLabel, 0, 2, 1, 1);

        progressBarBuffer = new QProgressBar(scrollAreaWidgetContents);
        progressBarBuffer->setObjectName(QString::fromUtf8("progressBarBuffer"));
        sizePolicy2.setHeightForWidth(progressBarBuffer->sizePolicy().hasHeightForWidth());
        progressBarBuffer->setSizePolicy(sizePolicy2);
        progressBarBuffer->setMinimumSize(QSize(150, 0));
        progressBarBuffer->setMaximumSize(QSize(16777215, 20));
        progressBarBuffer->setMaximum(16384);
        progressBarBuffer->setValue(0);

        gridLayout_2->addWidget(progressBarBuffer, 0, 4, 1, 1);

        BufferLabel = new QLabel(scrollAreaWidgetContents);
        BufferLabel->setObjectName(QString::fromUtf8("BufferLabel"));
        sizePolicy4.setHeightForWidth(BufferLabel->sizePolicy().hasHeightForWidth());
        BufferLabel->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(BufferLabel, 0, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 1, 0, 1, 1);

        progressBarData = new QProgressBar(scrollAreaWidgetContents);
        progressBarData->setObjectName(QString::fromUtf8("progressBarData"));
        sizePolicy2.setHeightForWidth(progressBarData->sizePolicy().hasHeightForWidth());
        progressBarData->setSizePolicy(sizePolicy2);
        progressBarData->setMinimumSize(QSize(150, 0));
        progressBarData->setMaximumSize(QSize(16777215, 20));
        progressBarData->setMaximum(50);
        progressBarData->setValue(0);

        gridLayout_2->addWidget(progressBarData, 1, 1, 1, 1);

        DataLabel = new QLabel(scrollAreaWidgetContents);
        DataLabel->setObjectName(QString::fromUtf8("DataLabel"));

        gridLayout_2->addWidget(DataLabel, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        progressBarPCBuffer = new QProgressBar(scrollAreaWidgetContents);
        progressBarPCBuffer->setObjectName(QString::fromUtf8("progressBarPCBuffer"));
        sizePolicy2.setHeightForWidth(progressBarPCBuffer->sizePolicy().hasHeightForWidth());
        progressBarPCBuffer->setSizePolicy(sizePolicy2);
        progressBarPCBuffer->setMinimumSize(QSize(150, 0));
        progressBarPCBuffer->setMaximumSize(QSize(16777215, 20));
        progressBarPCBuffer->setMaximum(4096);
        progressBarPCBuffer->setValue(0);

        gridLayout_2->addWidget(progressBarPCBuffer, 1, 4, 1, 1);

        PCBufferLabel = new QLabel(scrollAreaWidgetContents);
        PCBufferLabel->setObjectName(QString::fromUtf8("PCBufferLabel"));
        sizePolicy4.setHeightForWidth(PCBufferLabel->sizePolicy().hasHeightForWidth());
        PCBufferLabel->setSizePolicy(sizePolicy4);

        gridLayout_2->addWidget(PCBufferLabel, 1, 5, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 1, 6, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame);
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        ComboBox = new QComboBox(frame);
        ComboBox->setObjectName(QString::fromUtf8("ComboBox"));
        ComboBox->setMaxVisibleItems(1000);
        ComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        ComboBox->setFrame(true);

        horizontalLayout_4->addWidget(ComboBox);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_16);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        CanvasScope = new TQtWidget(frame);
        CanvasScope->setObjectName(QString::fromUtf8("CanvasScope"));
        CanvasScope->setMinimumSize(QSize(200, 300));

        horizontalLayout_9->addWidget(CanvasScope);

        CanvasSpectrum = new TQtWidget(frame);
        CanvasSpectrum->setObjectName(QString::fromUtf8("CanvasSpectrum"));
        CanvasSpectrum->setMinimumSize(QSize(200, 300));

        horizontalLayout_9->addWidget(CanvasSpectrum);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_5->addWidget(frame);

        verticalSpacer_2 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_13);

        CanvasHeatMap = new TQtWidget(scrollAreaWidgetContents);
        CanvasHeatMap->setObjectName(QString::fromUtf8("CanvasHeatMap"));
        sizePolicy2.setHeightForWidth(CanvasHeatMap->sizePolicy().hasHeightForWidth());
        CanvasHeatMap->setSizePolicy(sizePolicy2);
        CanvasHeatMap->setMinimumSize(QSize(450, 320));

        horizontalLayout_5->addWidget(CanvasHeatMap);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea);


        horizontalLayout_2->addWidget(DisplayBox);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        UI_NACdialog->setCentralWidget(centralwidget);
        menubar = new QMenuBar(UI_NACdialog);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1160, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuChannel_conf = new QMenu(menubar);
        menuChannel_conf->setObjectName(QString::fromUtf8("menuChannel_conf"));
        UI_NACdialog->setMenuBar(menubar);
#ifndef QT_NO_SHORTCUT
        NumberLabel->setBuddy(NumberSpinBox);
        ConsecutiveLabel->setBuddy(ConsecutiveSpinBox);
        MultiplicationLabel->setBuddy(FactorSpinBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(StartButton, ResetButton);
        QWidget::setTabOrder(ResetButton, NumberSpinBox);
        QWidget::setTabOrder(NumberSpinBox, ConsecutiveSpinBox);
        QWidget::setTabOrder(ConsecutiveSpinBox, FactorSpinBox);
        QWidget::setTabOrder(FactorSpinBox, ApplyButton);
        QWidget::setTabOrder(ApplyButton, Console);
        QWidget::setTabOrder(Console, scrollArea);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuChannel_conf->menuAction());
        menuFile->addAction(actionSave_Log_File_as);
        menuFile->addAction(actionExit);
        menuChannel_conf->addAction(action1_Channel);
        menuChannel_conf->addAction(action9_Channels);
        menuChannel_conf->addAction(action1000_Channels);

        retranslateUi(UI_NACdialog);

        ComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UI_NACdialog);
    } // setupUi

    void retranslateUi(QMainWindow *UI_NACdialog)
    {
        UI_NACdialog->setWindowTitle(QApplication::translate("UI_NACdialog", "PENeLOPE - GUI Network Access Control", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("UI_NACdialog", "E&xit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("UI_NACdialog", "X", 0, QApplication::UnicodeUTF8));
        actionSave_Log_File_as->setText(QApplication::translate("UI_NACdialog", "&Save Log-File as...", 0, QApplication::UnicodeUTF8));
        actionSave_Log_File_as->setShortcut(QApplication::translate("UI_NACdialog", "S", 0, QApplication::UnicodeUTF8));
        action9_Channels->setText(QApplication::translate("UI_NACdialog", "9 Channels", 0, QApplication::UnicodeUTF8));
        action1000_Channels->setText(QApplication::translate("UI_NACdialog", "1000 Channels", 0, QApplication::UnicodeUTF8));
        action1_Channel->setText(QApplication::translate("UI_NACdialog", "1 Channel", 0, QApplication::UnicodeUTF8));
        ControlBox->setTitle(QApplication::translate("UI_NACdialog", "Control", 0, QApplication::UnicodeUTF8));
        StartButton->setText(QApplication::translate("UI_NACdialog", "Save Data", 0, QApplication::UnicodeUTF8));
        ResetButton->setText(QApplication::translate("UI_NACdialog", "Reset SDU", 0, QApplication::UnicodeUTF8));
        SettingsBox->setTitle(QApplication::translate("UI_NACdialog", "Settings", 0, QApplication::UnicodeUTF8));
        NumberLabel->setText(QApplication::translate("UI_NACdialog", "Number of &samples per event:", 0, QApplication::UnicodeUTF8));
        ConsecutiveLabel->setText(QApplication::translate("UI_NACdialog", "Number of &consecutive samples:", 0, QApplication::UnicodeUTF8));
        MultiplicationLabel->setText(QApplication::translate("UI_NACdialog", "&Multiplication factor for signal detection:", 0, QApplication::UnicodeUTF8));
        ApplyButton->setText(QApplication::translate("UI_NACdialog", "Apply", 0, QApplication::UnicodeUTF8));
        DisplayBox->setTitle(QApplication::translate("UI_NACdialog", "Live Event Display", 0, QApplication::UnicodeUTF8));
        progressBarReads->setFormat(QApplication::translate("UI_NACdialog", "%v", 0, QApplication::UnicodeUTF8));
        ReadsLabel->setText(QApplication::translate("UI_NACdialog", "Reads / s", 0, QApplication::UnicodeUTF8));
        progressBarBuffer->setFormat(QApplication::translate("UI_NACdialog", "%v", 0, QApplication::UnicodeUTF8));
        BufferLabel->setText(QApplication::translate("UI_NACdialog", "Words in FPGA Buffer", 0, QApplication::UnicodeUTF8));
        progressBarData->setFormat(QApplication::translate("UI_NACdialog", "%v", 0, QApplication::UnicodeUTF8));
        DataLabel->setText(QApplication::translate("UI_NACdialog", "KB / s", 0, QApplication::UnicodeUTF8));
        progressBarPCBuffer->setFormat(QApplication::translate("UI_NACdialog", "%v", 0, QApplication::UnicodeUTF8));
        PCBufferLabel->setText(QApplication::translate("UI_NACdialog", "Words in PC Buffer", 0, QApplication::UnicodeUTF8));
        ComboBox->clear();
        ComboBox->insertItems(0, QStringList()
         << QApplication::translate("UI_NACdialog", "All channels", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UI_NACdialog", "Channel #9", 0, QApplication::UnicodeUTF8)
        );
        menuFile->setTitle(QApplication::translate("UI_NACdialog", "File", 0, QApplication::UnicodeUTF8));
        menuChannel_conf->setTitle(QApplication::translate("UI_NACdialog", "Channel conf", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UI_NACdialog: public Ui_UI_NACdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NACDIALOG_H

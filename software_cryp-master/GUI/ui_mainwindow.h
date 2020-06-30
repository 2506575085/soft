/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_23;
    QTabWidget *maintab;
    QWidget *cryption;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_4;
    QLabel *cry_key_in_label;
    QLineEdit *cry_key_in;
    QPushButton *cry_key_in_open;
    QGroupBox *cry_file;
    QGridLayout *gridLayout_6;
    QTreeWidget *cry_file_list;
    QPushButton *cry_file_remove;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *cry_file_add;
    QPushButton *cry_file_add_menu;
    QGridLayout *gridLayout_2;
    QComboBox *cry_algorithm;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cry_begin;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *cry_operation;
    QVBoxLayout *verticalLayout;
    QRadioButton *cry_operation_enc;
    QRadioButton *cry_operation_dec;
    QWidget *gen;
    QGridLayout *gridLayout_12;
    QLabel *label_3;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_8;
    QComboBox *gen_algorithm;
    QLabel *label_2;
    QGridLayout *gridLayout_9;
    QLineEdit *gen_pri;
    QLineEdit *gen_pub;
    QLabel *label_6;
    QPushButton *gen_pub_open;
    QLabel *label_5;
    QPushButton *gen_pri_open;
    QGridLayout *gridLayout_11;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;
    QWidget *hash;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_22;
    QGridLayout *gridLayout_15;
    QGridLayout *gridLayout_13;
    QLabel *label_7;
    QComboBox *hash_algorithm;
    QGroupBox *hash_operation;
    QGridLayout *gridLayout_18;
    QRadioButton *hash_operation_file;
    QRadioButton *hash_operation_string;
    QGroupBox *hash_file;
    QGridLayout *gridLayout_17;
    QGridLayout *gridLayout_16;
    QPushButton *hash_file_in_open;
    QLineEdit *hash_file_in;
    QGroupBox *hash_string;
    QGridLayout *gridLayout_19;
    QTextEdit *hash_string_in;
    QGridLayout *gridLayout_21;
    QGroupBox *hash_result;
    QGridLayout *gridLayout_14;
    QLineEdit *hash_result_out;
    QGridLayout *gridLayout_20;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *hash_begin;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_for_hash_file;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(570, 752);
        QIcon icon;
        icon.addFile(QString::fromUtf8("crypto.png"), QSize(), QIcon::Normal, QIcon::On);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_23 = new QGridLayout(centralWidget);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        maintab = new QTabWidget(centralWidget);
        maintab->setObjectName(QString::fromUtf8("maintab"));
        maintab->setStyleSheet(QString::fromUtf8(""));
        cryption = new QWidget();
        cryption->setObjectName(QString::fromUtf8("cryption"));
        gridLayout_7 = new QGridLayout(cryption);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        cry_key_in_label = new QLabel(cryption);
        cry_key_in_label->setObjectName(QString::fromUtf8("cry_key_in_label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cry_key_in_label->sizePolicy().hasHeightForWidth());
        cry_key_in_label->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(cry_key_in_label, 0, 0, 1, 1);

        cry_key_in = new QLineEdit(cryption);
        cry_key_in->setObjectName(QString::fromUtf8("cry_key_in"));

        gridLayout_4->addWidget(cry_key_in, 0, 1, 1, 1);

        cry_key_in_open = new QPushButton(cryption);
        cry_key_in_open->setObjectName(QString::fromUtf8("cry_key_in_open"));
        sizePolicy.setHeightForWidth(cry_key_in_open->sizePolicy().hasHeightForWidth());
        cry_key_in_open->setSizePolicy(sizePolicy);
        cry_key_in_open->setMaximumSize(QSize(30, 16777215));

        gridLayout_4->addWidget(cry_key_in_open, 0, 2, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 2, 0, 1, 1);

        cry_file = new QGroupBox(cryption);
        cry_file->setObjectName(QString::fromUtf8("cry_file"));
        gridLayout_6 = new QGridLayout(cry_file);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        cry_file_list = new QTreeWidget(cry_file);
        cry_file_list->setObjectName(QString::fromUtf8("cry_file_list"));

        gridLayout_6->addWidget(cry_file_list, 0, 0, 1, 3);

        cry_file_remove = new QPushButton(cry_file);
        cry_file_remove->setObjectName(QString::fromUtf8("cry_file_remove"));
        cry_file_remove->setFlat(false);

        gridLayout_6->addWidget(cry_file_remove, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cry_file_add = new QPushButton(cry_file);
        cry_file_add->setObjectName(QString::fromUtf8("cry_file_add"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cry_file_add->sizePolicy().hasHeightForWidth());
        cry_file_add->setSizePolicy(sizePolicy1);
        cry_file_add->setMinimumSize(QSize(75, 0));
        cry_file_add->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    margin-right: -18px;\n"
"}"));
        cry_file_add->setCheckable(false);
        cry_file_add->setFlat(false);

        horizontalLayout->addWidget(cry_file_add);

        cry_file_add_menu = new QPushButton(cry_file);
        cry_file_add_menu->setObjectName(QString::fromUtf8("cry_file_add_menu"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cry_file_add_menu->sizePolicy().hasHeightForWidth());
        cry_file_add_menu->setSizePolicy(sizePolicy2);
        cry_file_add_menu->setMaximumSize(QSize(18, 16777215));
        cry_file_add_menu->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    margin-left: -8px;\n"
"}"));
        cry_file_add_menu->setFlat(false);

        horizontalLayout->addWidget(cry_file_add_menu);


        gridLayout_6->addLayout(horizontalLayout, 1, 0, 1, 1);


        gridLayout_5->addWidget(cry_file, 3, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        cry_algorithm = new QComboBox(cryption);
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->addItem(QString());
        cry_algorithm->setObjectName(QString::fromUtf8("cry_algorithm"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(cry_algorithm->sizePolicy().hasHeightForWidth());
        cry_algorithm->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(cry_algorithm, 0, 2, 1, 1);

        label = new QLabel(cryption);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        cry_begin = new QPushButton(cryption);
        cry_begin->setObjectName(QString::fromUtf8("cry_begin"));

        horizontalLayout_2->addWidget(cry_begin);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_5->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        cry_operation = new QGroupBox(cryption);
        cry_operation->setObjectName(QString::fromUtf8("cry_operation"));
        sizePolicy3.setHeightForWidth(cry_operation->sizePolicy().hasHeightForWidth());
        cry_operation->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(cry_operation);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cry_operation_enc = new QRadioButton(cry_operation);
        cry_operation_enc->setObjectName(QString::fromUtf8("cry_operation_enc"));
        cry_operation_enc->setChecked(true);

        verticalLayout->addWidget(cry_operation_enc);

        cry_operation_dec = new QRadioButton(cry_operation);
        cry_operation_dec->setObjectName(QString::fromUtf8("cry_operation_dec"));

        verticalLayout->addWidget(cry_operation_dec);


        gridLayout_5->addWidget(cry_operation, 1, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout_5, 0, 0, 1, 1);

        maintab->addTab(cryption, QString());
        gen = new QWidget();
        gen->setObjectName(QString::fromUtf8("gen"));
        gridLayout_12 = new QGridLayout(gen);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_3 = new QLabel(gen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setScaledContents(false);
        label_3->setWordWrap(true);

        gridLayout_12->addWidget(label_3, 1, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gen_algorithm = new QComboBox(gen);
        gen_algorithm->addItem(QString());
        gen_algorithm->addItem(QString());
        gen_algorithm->addItem(QString());
        gen_algorithm->addItem(QString());
        gen_algorithm->addItem(QString());
        gen_algorithm->addItem(QString());
        gen_algorithm->setObjectName(QString::fromUtf8("gen_algorithm"));

        gridLayout_8->addWidget(gen_algorithm, 0, 2, 1, 1);

        label_2 = new QLabel(gen);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        gridLayout_8->addWidget(label_2, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_8, 0, 0, 1, 1);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gen_pri = new QLineEdit(gen);
        gen_pri->setObjectName(QString::fromUtf8("gen_pri"));

        gridLayout_9->addWidget(gen_pri, 0, 1, 1, 1);

        gen_pub = new QLineEdit(gen);
        gen_pub->setObjectName(QString::fromUtf8("gen_pub"));

        gridLayout_9->addWidget(gen_pub, 1, 1, 1, 1);

        label_6 = new QLabel(gen);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(label_6, 1, 0, 1, 1);

        gen_pub_open = new QPushButton(gen);
        gen_pub_open->setObjectName(QString::fromUtf8("gen_pub_open"));
        sizePolicy.setHeightForWidth(gen_pub_open->sizePolicy().hasHeightForWidth());
        gen_pub_open->setSizePolicy(sizePolicy);
        gen_pub_open->setMaximumSize(QSize(30, 16777215));

        gridLayout_9->addWidget(gen_pub_open, 1, 2, 1, 1);

        label_5 = new QLabel(gen);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(label_5, 0, 0, 1, 1);

        gen_pri_open = new QPushButton(gen);
        gen_pri_open->setObjectName(QString::fromUtf8("gen_pri_open"));
        sizePolicy.setHeightForWidth(gen_pri_open->sizePolicy().hasHeightForWidth());
        gen_pri_open->setSizePolicy(sizePolicy);
        gen_pri_open->setMaximumSize(QSize(30, 16777215));

        gridLayout_9->addWidget(gen_pri_open, 0, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 1, 0, 1, 1);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_4, 0, 0, 1, 1);

        pushButton = new QPushButton(gen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_11->addWidget(pushButton, 0, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_5, 0, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_11, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout_10->addItem(verticalSpacer, 3, 0, 1, 1);


        gridLayout_12->addLayout(gridLayout_10, 0, 0, 1, 1);

        maintab->addTab(gen, QString());
        hash = new QWidget();
        hash->setObjectName(QString::fromUtf8("hash"));
        gridLayout = new QGridLayout(hash);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_22 = new QGridLayout();
        gridLayout_22->setSpacing(6);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(6);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(6);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_7 = new QLabel(hash);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        gridLayout_13->addWidget(label_7, 0, 0, 1, 1);

        hash_algorithm = new QComboBox(hash);
        hash_algorithm->addItem(QString());
        hash_algorithm->addItem(QString());
        hash_algorithm->setObjectName(QString::fromUtf8("hash_algorithm"));

        gridLayout_13->addWidget(hash_algorithm, 0, 1, 1, 1);


        gridLayout_15->addLayout(gridLayout_13, 0, 0, 1, 1);

        hash_operation = new QGroupBox(hash);
        hash_operation->setObjectName(QString::fromUtf8("hash_operation"));
        sizePolicy3.setHeightForWidth(hash_operation->sizePolicy().hasHeightForWidth());
        hash_operation->setSizePolicy(sizePolicy3);
        gridLayout_18 = new QGridLayout(hash_operation);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        hash_operation_file = new QRadioButton(hash_operation);
        hash_operation_file->setObjectName(QString::fromUtf8("hash_operation_file"));
        hash_operation_file->setChecked(true);

        gridLayout_18->addWidget(hash_operation_file, 1, 0, 1, 1);

        hash_operation_string = new QRadioButton(hash_operation);
        hash_operation_string->setObjectName(QString::fromUtf8("hash_operation_string"));

        gridLayout_18->addWidget(hash_operation_string, 2, 0, 1, 1);


        gridLayout_15->addWidget(hash_operation, 1, 0, 1, 1);

        hash_file = new QGroupBox(hash);
        hash_file->setObjectName(QString::fromUtf8("hash_file"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(hash_file->sizePolicy().hasHeightForWidth());
        hash_file->setSizePolicy(sizePolicy4);
        gridLayout_17 = new QGridLayout(hash_file);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        hash_file_in_open = new QPushButton(hash_file);
        hash_file_in_open->setObjectName(QString::fromUtf8("hash_file_in_open"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(hash_file_in_open->sizePolicy().hasHeightForWidth());
        hash_file_in_open->setSizePolicy(sizePolicy5);
        hash_file_in_open->setMaximumSize(QSize(30, 16777215));

        gridLayout_16->addWidget(hash_file_in_open, 0, 1, 1, 1);

        hash_file_in = new QLineEdit(hash_file);
        hash_file_in->setObjectName(QString::fromUtf8("hash_file_in"));

        gridLayout_16->addWidget(hash_file_in, 0, 0, 1, 1);


        gridLayout_17->addLayout(gridLayout_16, 0, 0, 1, 1);


        gridLayout_15->addWidget(hash_file, 3, 0, 1, 1);

        hash_string = new QGroupBox(hash);
        hash_string->setObjectName(QString::fromUtf8("hash_string"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(hash_string->sizePolicy().hasHeightForWidth());
        hash_string->setSizePolicy(sizePolicy6);
        gridLayout_19 = new QGridLayout(hash_string);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        hash_string_in = new QTextEdit(hash_string);
        hash_string_in->setObjectName(QString::fromUtf8("hash_string_in"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(hash_string_in->sizePolicy().hasHeightForWidth());
        hash_string_in->setSizePolicy(sizePolicy7);

        gridLayout_19->addWidget(hash_string_in, 0, 0, 1, 1);


        gridLayout_15->addWidget(hash_string, 2, 0, 1, 1);


        gridLayout_22->addLayout(gridLayout_15, 0, 0, 1, 1);

        gridLayout_21 = new QGridLayout();
        gridLayout_21->setSpacing(6);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        hash_result = new QGroupBox(hash);
        hash_result->setObjectName(QString::fromUtf8("hash_result"));
        sizePolicy4.setHeightForWidth(hash_result->sizePolicy().hasHeightForWidth());
        hash_result->setSizePolicy(sizePolicy4);
        gridLayout_14 = new QGridLayout(hash_result);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        hash_result_out = new QLineEdit(hash_result);
        hash_result_out->setObjectName(QString::fromUtf8("hash_result_out"));

        gridLayout_14->addWidget(hash_result_out, 0, 0, 1, 1);


        gridLayout_21->addWidget(hash_result, 0, 0, 1, 1);

        gridLayout_20 = new QGridLayout();
        gridLayout_20->setSpacing(6);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_20->addItem(horizontalSpacer_6, 0, 0, 1, 1);

        hash_begin = new QPushButton(hash);
        hash_begin->setObjectName(QString::fromUtf8("hash_begin"));

        gridLayout_20->addWidget(hash_begin, 0, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_20->addItem(horizontalSpacer_7, 0, 2, 1, 1);


        gridLayout_21->addLayout(gridLayout_20, 1, 0, 1, 1);


        gridLayout_22->addLayout(gridLayout_21, 2, 0, 1, 1);

        verticalSpacer_for_hash_file = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        gridLayout_22->addItem(verticalSpacer_for_hash_file, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_22, 0, 0, 1, 1);

        maintab->addTab(hash, QString());

        gridLayout_23->addWidget(maintab, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(maintab, cry_algorithm);
        QWidget::setTabOrder(cry_algorithm, cry_operation_enc);
        QWidget::setTabOrder(cry_operation_enc, cry_operation_dec);
        QWidget::setTabOrder(cry_operation_dec, cry_key_in);
        QWidget::setTabOrder(cry_key_in, cry_key_in_open);
        QWidget::setTabOrder(cry_key_in_open, cry_file_list);
        QWidget::setTabOrder(cry_file_list, cry_file_add);
        QWidget::setTabOrder(cry_file_add, cry_file_add_menu);
        QWidget::setTabOrder(cry_file_add_menu, cry_file_remove);
        QWidget::setTabOrder(cry_file_remove, cry_begin);
        QWidget::setTabOrder(cry_begin, gen_algorithm);
        QWidget::setTabOrder(gen_algorithm, gen_pri);
        QWidget::setTabOrder(gen_pri, gen_pri_open);
        QWidget::setTabOrder(gen_pri_open, gen_pub);
        QWidget::setTabOrder(gen_pub, gen_pub_open);
        QWidget::setTabOrder(gen_pub_open, hash_algorithm);
        QWidget::setTabOrder(hash_algorithm, hash_operation_file);
        QWidget::setTabOrder(hash_operation_file, hash_operation_string);
        QWidget::setTabOrder(hash_operation_string, hash_string_in);
        QWidget::setTabOrder(hash_string_in, hash_file_in);
        QWidget::setTabOrder(hash_file_in, hash_file_in_open);
        QWidget::setTabOrder(hash_file_in_open, hash_result_out);
        QWidget::setTabOrder(hash_result_out, hash_begin);
        QWidget::setTabOrder(hash_begin, pushButton);

        retranslateUi(MainWindow);

        maintab->setCurrentIndex(0);
        cry_file_add->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Crypto", nullptr));
        cry_key_in_label->setText(QApplication::translate("MainWindow", "\345\257\206\351\222\245\350\276\223\345\205\245", nullptr));
        cry_key_in_open->setText(QApplication::translate("MainWindow", "...", nullptr));
        cry_file->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = cry_file_list->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        cry_file_remove->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        cry_file_add->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240...", nullptr));
        cry_algorithm->setItemText(0, QApplication::translate("MainWindow", "AES", nullptr));
        cry_algorithm->setItemText(1, QApplication::translate("MainWindow", "DES", nullptr));
        cry_algorithm->setItemText(2, QApplication::translate("MainWindow", "RSA-1024", nullptr));
        cry_algorithm->setItemText(3, QApplication::translate("MainWindow", "RSA-2048", nullptr));
        cry_algorithm->setItemText(4, QApplication::translate("MainWindow", "RSA-4096", nullptr));
        cry_algorithm->setItemText(5, QApplication::translate("MainWindow", "ECC-secp256k1", nullptr));
        cry_algorithm->setItemText(6, QApplication::translate("MainWindow", "ECC-secp256r1", nullptr));
        cry_algorithm->setItemText(7, QApplication::translate("MainWindow", "ECC-SM2", nullptr));

        label->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225\351\200\211\346\213\251", nullptr));
        cry_begin->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        cry_operation->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234\351\200\211\346\213\251", nullptr));
        cry_operation_enc->setText(QApplication::translate("MainWindow", "\345\212\240\345\257\206", nullptr));
        cry_operation_dec->setText(QApplication::translate("MainWindow", "\350\247\243\345\257\206", nullptr));
        maintab->setTabText(maintab->indexOf(cryption), QApplication::translate("MainWindow", "\345\212\240\345\257\206/\350\247\243\345\257\206", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\260\217\346\217\220\347\244\272\357\274\232\345\217\252\346\234\211\351\235\236\345\257\271\347\247\260\345\212\240\345\257\206\347\256\227\346\263\225\346\211\215\351\234\200\350\246\201\347\224\237\346\210\220\345\257\206\351\222\245\345\257\271\343\200\202", nullptr));
        gen_algorithm->setItemText(0, QApplication::translate("MainWindow", "RSA-1024", nullptr));
        gen_algorithm->setItemText(1, QApplication::translate("MainWindow", "RSA-2048", nullptr));
        gen_algorithm->setItemText(2, QApplication::translate("MainWindow", "RSA-4096", nullptr));
        gen_algorithm->setItemText(3, QApplication::translate("MainWindow", "ECC-secp256k1", nullptr));
        gen_algorithm->setItemText(4, QApplication::translate("MainWindow", "ECC-secp256r1", nullptr));
        gen_algorithm->setItemText(5, QApplication::translate("MainWindow", "ECC-SM2", nullptr));

        label_2->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225\351\200\211\346\213\251", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\345\205\254\351\222\245\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        gen_pub_open->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\347\247\201\351\222\245\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        gen_pri_open->setText(QApplication::translate("MainWindow", "...", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220", nullptr));
        maintab->setTabText(maintab->indexOf(gen), QApplication::translate("MainWindow", "\345\257\206\351\222\245\345\257\271\347\224\237\346\210\220", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\347\256\227\346\263\225\351\200\211\346\213\251", nullptr));
        hash_algorithm->setItemText(0, QApplication::translate("MainWindow", "MD5", nullptr));
        hash_algorithm->setItemText(1, QApplication::translate("MainWindow", "SHA256", nullptr));

        hash_operation->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234\351\200\211\346\213\251", nullptr));
        hash_operation_file->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\346\223\215\344\275\234", nullptr));
        hash_operation_string->setText(QApplication::translate("MainWindow", "\345\255\227\347\254\246\344\270\262\346\223\215\344\275\234", nullptr));
        hash_file->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266\350\276\223\345\205\245", nullptr));
        hash_file_in_open->setText(QApplication::translate("MainWindow", "...", nullptr));
        hash_string->setTitle(QApplication::translate("MainWindow", "\345\255\227\347\254\246\344\270\262\350\276\223\345\205\245", nullptr));
        hash_result->setTitle(QApplication::translate("MainWindow", "\347\273\223\346\236\234", nullptr));
        hash_begin->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        maintab->setTabText(maintab->indexOf(hash), QApplication::translate("MainWindow", "\345\223\210\345\270\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtConcurrent/QtConcurrentRun.h>
#include <QDir>
#include <QFileDialog>
#include <QMenu>
#include <QString>

#include <iomanip>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <string>

#include "../AES/AES.h"

#include "../DES/des.h"

#include "../RSA/RSA_Decryption.h"
#include "../RSA/RSA_Encryption.h"
#include "../RSA/RSA_Generate.h"

#include "../ECC/ECC.h"

#include "../Hash/md5.h"
#include "../Hash/sha256.h"

QTreeWidgetItem *FindChild(QTreeWidgetItem *root, std::string str,
                           bool is_dir = true);
void AddFile(QTreeWidgetItem *root, std::string path);
void AddDir(QTreeWidgetItem *root, QString path);
void DeleteFile(QTreeWidgetItem *node, QTreeWidgetItem *root);
void GetAllFile(std::queue<std::string> &list, QTreeWidgetItem *cur,
                std::string cur_path = "");
std::string toStdString(QString s);
unsigned long long StringtoULL(const std::string s);
void Stringto128(const std::string s, unsigned long long *a);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this, SIGNAL(finish()), this, SLOT(enable_tab()));
    connect(this, SIGNAL(setText(QLineEdit *, QString)), this,
            SLOT(setTextFun(QLineEdit *, QString)));

    auto menu = new QMenu();
    auto add_dir = new QAction(menu);
    add_dir->setText(QStringLiteral("添加文件夹"));
    connect(add_dir, SIGNAL(triggered()), this, SLOT(add_dir_dialog()));
    menu->addAction(add_dir);
    this->ui->cry_file_add_menu->setMenu(menu);

    UpdataUI();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_cry_algorithm_currentIndexChanged(const QString &) {
    UpdataUI();
}

void MainWindow::on_cry_operation_enc_toggled(bool) { UpdataUI(); }

void MainWindow::on_cry_operation_dec_toggled(bool) { UpdataUI(); }

void MainWindow::on_hash_operation_file_clicked() { UpdataUI(); }

void MainWindow::on_hash_operation_string_clicked() { UpdataUI(); }

void MainWindow::UpdataUI() {
    static auto Spacer = this->ui->verticalSpacer_for_hash_file;
    std::string algorithm =
        this->ui->cry_algorithm->currentText().toStdString();
    if (algorithm.substr(0, 3) == "RSA" || algorithm.substr(0, 3) == "ECC") {
        if (this->ui->cry_operation_enc->isChecked()) {
            this->ui->cry_key_in_open->setVisible(true);
            this->ui->cry_key_in_label->setText(QStringLiteral("公钥路径"));
        } else {
            this->ui->cry_key_in_open->setVisible(true);
            this->ui->cry_key_in_label->setText(QStringLiteral("私钥路径"));
        }
    } else {
        this->ui->cry_key_in_open->setVisible(false);
        this->ui->cry_key_in_label->setText(QStringLiteral("密钥输入"));
    }

    if (this->ui->hash_operation_file->isChecked()) {
        this->ui->hash_string->setVisible(false);
        this->ui->hash_file->setVisible(true);
        this->ui->gridLayout_22->removeItem(Spacer);
        this->ui->gridLayout_22->addItem(Spacer, 1, 0);
    } else if (this->ui->hash_operation_string->isChecked()) {
        this->ui->hash_string->setVisible(true);
        this->ui->hash_file->setVisible(false);
        this->ui->gridLayout_22->removeItem(Spacer);
    }
}

void MainWindow::on_cry_file_remove_clicked() {
    auto cur = this->ui->cry_file_list->currentItem();
    DeleteFile(cur, this->ui->cry_file_list->invisibleRootItem());
}

void DeleteFile(QTreeWidgetItem *node, QTreeWidgetItem *root) {
    if (node != nullptr) {
        auto parent = node->parent();
        if (parent == nullptr) parent = root;
        parent->removeChild(node);
        if (parent != root && parent->childCount() == 0)
            DeleteFile(parent, root);
        delete node;
    }
}

void MainWindow::on_cry_file_add_clicked() {
    QStringList files = QFileDialog::getOpenFileNames(
        this, QStringLiteral("打开文件"), "/", "", 0);
    for (auto _path : files) {
        std::string path = _path.toStdString();
        QTreeWidgetItem *root = this->ui->cry_file_list->invisibleRootItem();
        AddFile(root, path);
    }
}

void MainWindow::add_dir_dialog() {
    QString path = QFileDialog::getExistingDirectory(
        this, QStringLiteral("打开目录"), "/", QFileDialog::ShowDirsOnly);
    if (path != "") AddDir(this->ui->cry_file_list->invisibleRootItem(), path);
}

void AddDir(QTreeWidgetItem *root, QString path) {
    QDir dir(path);
    if (!dir.exists()) return;
    dir.setFilter(QDir::Dirs | QDir::Files);
    auto list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i++) {
        if (list[i].fileName() == "." || list[i].fileName() == "..") continue;
        if (list[i].isDir()) {
            AddDir(root, list[i].filePath());
        } else {
            AddFile(root, list[i].filePath().toStdString());
        }
    }
}

void AddFile(QTreeWidgetItem *root, std::string path) {
    auto cur = FindChild(root, path.substr(0, 2), true);

    std::regex reg("/[^/]*");
    auto begin = std::sregex_iterator(path.begin(), path.end(), reg);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end;) {
        std::string name = it->str().substr(1);
        cur = FindChild(cur, name, ++it != end);
    }
}

QTreeWidgetItem *FindChild(QTreeWidgetItem *root, std::string str,
                           bool is_dir) {
    QTreeWidgetItem *ans = nullptr;
    for (int i = 0; i < root->childCount(); i++) {
        auto cur = root->child(i);
        if (cur->text(0).toStdString() == str) {
            ans = cur;
            break;
        }
    }
    if (ans == nullptr) {  // 新的盘符
        ans = new QTreeWidgetItem((QTreeWidgetItem *)nullptr);
        int index = 0;
        while ((!is_dir && root->childCount() > index &&
                root->child(index)->childCount() > 0) ||
               (root->childCount() > index &&
                str > root->child(index)->text(0).toStdString())) {
            index++;
        }
        root->insertChild(index, ans);
        ans->setText(0, QString::fromStdString(str));
        ans->setExpanded(true);
    }
    return ans;
}

void MainWindow::on_cry_key_in_open_clicked() {
    QString path = QFileDialog::getOpenFileName(
        this, QStringLiteral("打开文件"), "/", "", 0);
    this->ui->cry_key_in->setText(path);
}

void MainWindow::on_hash_file_in_open_clicked() {
    QString path = QFileDialog::getOpenFileName(
        this, QStringLiteral("打开文件"), "/", "", 0);
    this->ui->hash_file_in->setText(path);
}

void MainWindow::on_cry_begin_clicked() {
    this->ui->maintab->setEnabled(false);
    QWidget::repaint();
    QtConcurrent::run([&]() {
        std::string algorithm =
            this->ui->cry_algorithm->currentText().toStdString();
        std::queue<std::string> file_list;
        GetAllFile(file_list, this->ui->cry_file_list->invisibleRootItem());
        while (!file_list.empty() && file_list.front() != "") {
            std::string key = this->ui->cry_key_in->text().toStdString();
            if (this->ui->cry_operation_enc->isChecked()) {  // 加密
                if (algorithm == "AES") {
                    unsigned long long key128[2];
                    Stringto128(key, key128);
                    aesEncryptFile((uint8_t *)key128, 16,
                                   file_list.front().c_str(),
                                   (file_list.front() + ".enc").c_str());
                } else if (algorithm == "DES") {
                    unsigned long long kull = StringtoULL(key);
                    std::bitset<64> kbs(kull);
                    DES::Encry(file_list.front(), kbs,
                               file_list.front() + ".enc");
                } else if (algorithm.substr(0, 3) == "RSA") {
                    if (algorithm == "RSA-1024") {
                        RSA::PublicKey<1024 / 64> pub;
                        pub.read(key);
                        RSA::EncryptionFile(pub, file_list.front(),
                                            file_list.front() + ".enc");
                    } else if (algorithm == "RSA-2048") {
                        RSA::PublicKey<2048 / 64> pub;
                        pub.read(key);
                        RSA::EncryptionFile(pub, file_list.front(),
                                            file_list.front() + ".enc");
                    } else if (algorithm == "RSA-4096") {
                        RSA::PublicKey<4096 / 64> pub;
                        pub.read(key);
                        RSA::EncryptionFile(pub, file_list.front(),
                                            file_list.front() + ".enc");
                    }
                } else if (algorithm.substr(0, 3) == "ECC") {
                    ECC::PublicKey pub;
                    pub.read(key);
                    if (algorithm == "ECC-secp256k1") {
                        ECC::secp256k1.encryptFile(pub, file_list.front(),
                                                   file_list.front() + ".enc");
                    } else if (algorithm == "ECC-secp256r1") {
                        ECC::secp256r1.encryptFile(pub, file_list.front(),
                                                   file_list.front() + ".enc");
                    } else if (algorithm == "ECC-SM2") {
                        ECC::SM2.encryptFile(pub, file_list.front(),
                                             file_list.front() + ".enc");
                    }
                }
            } else if (this->ui->cry_operation_dec->isChecked()) {  // 解密
                std::string output_name = file_list.front();
                output_name = output_name.substr(0, output_name.length() - 4);
                if (algorithm == "AES") {
                    unsigned long long key128[2];
                    Stringto128(key, key128);
                    aesDecryptFile((uint8_t *)key128, 16,
                                   file_list.front().c_str(),
                                   output_name.c_str());
                } else if (algorithm == "DES") {
                    unsigned long long kull = StringtoULL(key);
                    std::bitset<64> kbs(kull);
                    DES::Decry(file_list.front(), kbs, output_name);
                } else if (algorithm.substr(0, 3) == "RSA") {
                    if (algorithm == "RSA-1024") {
                        RSA::PrivateKey<1024 / 64> pri;
                        pri.read(key);
                        RSA::DecryptionFile(pri, file_list.front(),
                                            output_name);
                    } else if (algorithm == "RSA-2048") {
                        RSA::PrivateKey<2048 / 64> pri;
                        pri.read(key);
                        RSA::DecryptionFile(pri, file_list.front(),
                                            output_name);
                    } else if (algorithm == "RSA-4096") {
                        RSA::PrivateKey<4096 / 64> pri;
                        pri.read(key);
                        RSA::DecryptionFile(pri, file_list.front(),
                                            output_name);
                    }
                } else if (algorithm.substr(0, 3) == "ECC") {
                    ECC::PrivateKey pri;
                    pri.read(key);
                    if (algorithm == "ECC-secp256k1") {
                        ECC::secp256k1.decryptFile(pri, file_list.front(),
                                                   output_name);
                    } else if (algorithm == "ECC-secp256r1") {
                        ECC::secp256r1.decryptFile(pri, file_list.front(),
                                                   output_name);
                    } else if (algorithm == "ECC-SM2") {
                        ECC::SM2.decryptFile(pri, file_list.front(),
                                             output_name);
                    }
                }
            }
            file_list.pop();
        }
        emit finish();
    });
}

void MainWindow::enable_tab() {
    this->ui->maintab->setEnabled(true);
    QWidget::repaint();
}

void MainWindow::setTextFun(QLineEdit *le, QString s) { le->setText(s); }

void GetAllFile(std::queue<std::string> &list, QTreeWidgetItem *cur,
                std::string cur_path) {
    if (cur->childCount() != 0) {
        for (int i = 0; i < cur->childCount(); i++) {
            GetAllFile(list, cur->child(i),
                       cur_path + (cur_path != "" ? "/" : "") +
                           toStdString(cur->text(0)));
        }
    } else {
        list.push(cur_path + (cur_path != "" ? "/" : "") +
                  toStdString(cur->text(0)));
    }
}

std::string toStdString(QString s) {
    return std::string((const char *)s.toLocal8Bit());
}

void MainWindow::on_hash_begin_clicked() {
    this->ui->maintab->setEnabled(false);
    QWidget::repaint();
    QtConcurrent::run([&]() {
        std::string algorithm =
            this->ui->hash_algorithm->currentText().toStdString();

        std::string hash;
        if (this->ui->hash_operation_file->isChecked()) {
            std::string path;
            path = toStdString(this->ui->hash_file_in->text());
            if (algorithm == "SHA256") {
                char sha256[65];
                FileSHA256(path.c_str(), sha256);
                hash = sha256;
            } else if (algorithm == "MD5") {
                md_5 MD5_1;
                unsigned char result1[16];
                Init(&MD5_1);
                Update_file(&MD5_1, path);
                final_step(&MD5_1, result1);
                std::stringstream s;
                for (int i = 0; i < 16; i++)
                    s << std::hex << (unsigned)result1[i];
                s >> hash;
            }
        } else if (this->ui->hash_operation_string->isChecked()) {
            std::string message;
            message = toStdString(this->ui->hash_string_in->toPlainText());
            if (algorithm == "SHA256") {
                char sha256[65];
                sha_256(sha256, message.c_str());
                hash = sha256;
            } else if (algorithm == "MD5") {
                md_5 MD5;
                hash = fengzhuang(message, &MD5);
            }
        }
        this->ui->hash_result_out->setText(QString::fromStdString(hash));

        emit finish();
    });
}

void MainWindow::on_gen_pri_open_clicked() {
    QString path = QFileDialog::getSaveFileName(
        this, QStringLiteral("保存文件"), "/", "key (*.key)", 0);
    this->ui->gen_pri->setText(path);
}

void MainWindow::on_gen_pub_open_clicked() {
    QString path = QFileDialog::getSaveFileName(
        this, QStringLiteral("保存文件"), "/", "key (*.key)", 0);
    this->ui->gen_pub->setText(path);
}

void MainWindow::on_pushButton_clicked() {
    this->ui->maintab->setEnabled(false);
    QWidget::repaint();
    QtConcurrent::run([&]() {
        std::string algorithm =
            this->ui->gen_algorithm->currentText().toStdString();

        std::string pub_path = toStdString(this->ui->gen_pub->text()),
                    pri_path = toStdString(this->ui->gen_pri->text());
        if (algorithm.substr(0, 3) == "RSA") {
            if (algorithm == "RSA-1024") {
                RSA::PublicKey<1024 / 64> pub;
                RSA::PrivateKey<1024 / 64> pri;
                RSA::Generate(pub, pri);
                pub.save(pub_path);
                pri.save(pri_path);
            } else if (algorithm == "RSA-2048") {
                RSA::PublicKey<2048 / 64> pub;
                RSA::PrivateKey<2048 / 64> pri;
                RSA::Generate(pub, pri);
                pub.save(pub_path);
                pri.save(pri_path);
            } else if (algorithm == "RSA-4096") {
                RSA::PublicKey<4096 / 64> pub;
                RSA::PrivateKey<4096 / 64> pri;
                RSA::Generate(pub, pri);
                pub.save(pub_path);
                pri.save(pri_path);
            }
        } else if (algorithm.substr(0, 3) == "ECC") {
            ECC::PublicKey pub;
            ECC::PrivateKey pri = ECC::PrivateKey::Generate();
            if (algorithm == "ECC-secp256k1") {
                pub = ECC::secp256k1.GenPubKey(pri);
            } else if (algorithm == "ECC-secp256r1") {
                pub = ECC::secp256r1.GenPubKey(pri);
            } else if (algorithm == "ECC-SM2") {
                pub = ECC::SM2.GenPubKey(pri);
            }
            pub.save(pub_path);
            pri.save(pri_path);
        }
        emit finish();
    });
}

unsigned long long StringtoULL(const std::string s) {
    char sha256[65];
    sha_256(sha256, s.c_str());
    sha256[16] = '\0';
    std::stringstream ss(sha256);
    unsigned long long k;
    ss >> std::hex >> k;
    return k;
}

void Stringto128(const std::string s, unsigned long long *a) {
    char sha256[65];
    sha_256(sha256, s.c_str());
    char z[17];
    memcpy(z, sha256, 16);
    z[16] = '\0';
    std::stringstream ss(z);
    ss >> *a;
    memcpy(z, sha256 + 16, 16);
    ss << z;
    ss >> *(a + 1);
}

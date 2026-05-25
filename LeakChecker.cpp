#include "LeakChecker.h"
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QTimer>

void LeakChecker::check(const QString& password)
{
    QString hash = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex().toUpper());
    QString prefix = hash.left(5);
    QString suffix = hash.mid(5);

    QUrl url("https://api.pwnedpasswords.com/range/" + prefix);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "HamPassword-Checker/1.0");

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [this, manager, suffix](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QString data = reply->readAll();
            QStringList lines = data.split("\r\n", Qt::SkipEmptyParts);
            int leakCount = 0;
            for (const QString& line : lines) {
                if (line.startsWith(suffix)) {
                    bool ok;
                    leakCount = line.split(':')[1].toInt(&ok);
                    break;
                }
            }
            if (leakCount > 0) {
                emit resultReady(QString("⚠️ НАЙДЕН В %1 УТЕЧКАХ!").arg(leakCount), false);
            } else {
                emit resultReady("✓ Пароль безопасен", true);
            }
        } else {
            emit resultReady("❌ Ошибка проверки", false);
        }
        manager->deleteLater();
    });
    manager->get(request);
}

LeakChecker& LeakChecker::instance()
{
    static LeakChecker inst;
    return inst;
}
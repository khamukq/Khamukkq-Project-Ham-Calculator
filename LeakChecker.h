#ifndef LEAKCHECKER_H
#define LEAKCHECKER_H

#include <QObject>

class LeakChecker : public QObject
{
    Q_OBJECT

public:
    static LeakChecker& instance();
    void check(const QString& password);

signals:
    void resultReady(const QString& result, bool isSafe);

private:
    LeakChecker() = default;
    LeakChecker(const LeakChecker&) = delete;
    LeakChecker& operator=(const LeakChecker&) = delete;
};

#endif
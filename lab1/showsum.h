#ifndef SHOWSUM_H
#define SHOWSUM_H

#include <QWidget>
#include <QThread>
#include <stdio.h>

namespace Ui {
class ShowSum;
}

class ShowSum : public QWidget
{
    Q_OBJECT

public:
    explicit ShowSum(QWidget *parent = 0);
    ~ShowSum();

public slots:
    void handleResult(const QString& s);

private:
    Ui::ShowSum *ui;
    int row;
};

class WorkerThread_sum : public QThread
{
    Q_OBJECT

public:
    void run()
    {
        sum = 0;
        char res[30];
        for(int i = 1; i <= 100; ++i)
        {
            sprintf(res, "%d + %d = %d\n", sum, i, sum + i);
            emit resultReady(res);
            sum += i;
            sleep(3);
        }
    }

private:
    int sum;

signals:
    void resultReady(const QString& s);
};

#endif // SHOWSUM_H

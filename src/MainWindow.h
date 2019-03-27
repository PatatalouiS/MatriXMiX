


#include <QMainWindow>
#include <QPushButton>
#include <QList>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
    
    MainWindow ();
    ~MainWindow ();
    
    signals:
    
    public slots:
    
    void computeChoice (const unsigned int choice);
    
    private:
    
    QList<QPushButton*> operations;
};

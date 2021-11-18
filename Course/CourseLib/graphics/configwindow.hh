#ifndef CONFIGWINDOW_HH
#define CONFIGWINDOW_HH

#include <QDialog>
#include <QTime>


namespace Ui {
class KonffiIkkuna;
}

namespace CourseSide
{

/**
 * @brief Configuration-dialog
 */
class ConfigWindow : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Constructor
     * @param parent QDialogin parent.
     * @pre -
     */
    explicit ConfigWindow(QWidget *parent = 0);

    /**
     * @brief Destructor.
     */
    virtual ~ConfigWindow();

    /**
     * @brief Specialized QDialog::exec. Runs the dialog.
     * @return QDialog::Accepted, if user accepeted configuration. Else returns QDialog::Rejected.
     * @pre -
     * @post Emits configChanged-signal, if user accepted configuration.
     */
    virtual int exec();


signals:

    /**
     * @brief Signal, that signals of a accepted configuration.
     * @param time Game start time.
     * @param debug True, if using debug-configuration of one bus.
     */
    void configChanged(QTime time, bool debug);

private:
    Ui::KonffiIkkuna *ui;
};

} // CourseSide

#endif // CONFIGWINDOW_HH

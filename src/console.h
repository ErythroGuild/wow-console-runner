#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDateTime>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QProcess>
#include <QRegularExpression>
#include <QScrollBar>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>
#include <QWidget>

#include <QFileDialog>

#include "utils.h"
#include "consolehost.h"

class Console : public QObject
{
	Q_OBJECT

public:
	inline static const unsigned int lines_buf = 1024;
	inline static const unsigned int chars_buf = 80 * lines_buf;

	// Cannot be static. <APPNAME> isn't registered correctly on static init,
	// and `QStandardPaths::AppDataLocation` is not known.
	const QString path_logs =
			QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
			"/Logs/";

	Console(QWidget* parent, QString path = "");
	~Console();

	ConsoleHost* get_host() { return host; }
	QString get_path() { return host->get_path(); }

signals:
	void exe_updated(QString name);

private:
	inline static const QString runs_separator = "\n\n";

	QWidget* parent;
	ConsoleHost* host;
	QProcess* process;
	QTextStream logger;

private slots:
	// console display
	void pipe_output();

	// executable path
	void set_path();

	// action buttons
	void start_process();
	void stop_process();
	void open_logs();
};

#endif // CONSOLE_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rgb2lab.h"

#include <QMainWindow>

#include <vector>
#include <stdint.h>

namespace Ui {
class MainWindow;
}

struct ColorData {
	LAB colorLab;
	uint32_t colorRgb;
	uint64_t count;
};

class MainWindow : public QMainWindow
{
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent * event) override;

	bool eventFilter(QObject *, QEvent *) override;

private:
	Ui::MainWindow *ui;

	std::vector<ColorData> _colorsData;
};

#endif // MAINWINDOW_H

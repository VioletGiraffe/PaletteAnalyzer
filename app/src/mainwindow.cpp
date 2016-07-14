#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDropEvent>
#include <QImage>
#include <QMimeData>
#include <QPainter>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	setAcceptDrops(true);

	QWidget * displayWidget = new QWidget(this);
	setCentralWidget(displayWidget);
	displayWidget->installEventFilter(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
		event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event)
{
	QTime timer;
	timer.start();
	_colorsData = std::vector<ColorData>(0xFFFFFFU + 1U, {{0.0, 0.0, 0.0}, 0U, 0ULL});

	qDebug() << "Clearing _colorsData took" << timer.elapsed() << "ms";
	timer.restart();

	if (event->mimeData()->hasUrls())
	{
		QImage img(event->mimeData()->urls().front().toLocalFile());

		for (int h = 0; h < img.height(); ++h)
		{
			for (int w = 0; w < img.width(); ++w)
			{
				QRgb color = img.pixel(w, h);
				++_colorsData[color & RGB_MASK].count;
				_colorsData[color & RGB_MASK].colorRgb = color;
			}
		}
	}

	qDebug() << "Scanning the image took" << timer.elapsed() << "ms";
	timer.restart();

	_colorsData.erase(std::remove_if(_colorsData.begin(), _colorsData.end(), [](const ColorData& colorData){
		return colorData.count == 0;
	}), _colorsData.end());

	qDebug() << "Erasing non-existing colors took" << timer.elapsed() << "ms";
	timer.restart();

	std::sort(_colorsData.begin(), _colorsData.end(), [](const ColorData& l, const ColorData& r){
		return l.count > r.count;
	});

	qDebug() << "Sorting colors took" << timer.elapsed() << "ms";

	for (ColorData& color: _colorsData)
		color.colorLab = rgb2lab(color.colorRgb);

	

	centralWidget()->update();
}

bool MainWindow::eventFilter(QObject * object, QEvent * event)
{
	if (event->type() == QEvent::Paint && _colorsData.size() >= 3)
	{
		QPainter p((QWidget*)object);
		auto color = _colorsData.begin();
		p.fillRect(0, 0, width()/3, height(), QColor::fromRgb(((color->colorRgb) >> 16) & 0xFFU, ((color->colorRgb) >> 8) & 0xFFU, (color->colorRgb) & 0xFFU));

		color = color + 1000;

		p.fillRect(width()/3, 0, width()/3, height(), QColor::fromRgb(((color->colorRgb) >> 16) & 0xFFU, ((color->colorRgb) >> 8) & 0xFFU, (color->colorRgb) & 0xFFU));

		color += 1000;
		p.fillRect(2 * width() / 3, 0, width() / 3, height(), QColor::fromRgb(((color->colorRgb) >> 16) & 0xFFU, ((color->colorRgb) >> 8) & 0xFFU, (color->colorRgb) & 0xFFU));

		return false;
	}

	return QMainWindow::eventFilter(object, event);
}

#include <obs-module.h>
#include <obs-frontend-api.h>

#include <QMainWindow>
#include <QFrame>
#include <QLayout>
#include <QPushButton>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("exit-button-plugin", "en-US")

static void plugin_main()
{
	auto mainWindow = static_cast<QMainWindow *>(obs_frontend_get_main_window());
	if (!mainWindow)
		return;

	auto controlsFrame = mainWindow->findChild<QFrame *>("controlsFrame");
	if (!controlsFrame)
		return;

	auto buttonsVLayout = controlsFrame->findChild<QVBoxLayout *>("buttonsVLayout");
	if (!buttonsVLayout)
		return;

	auto exitButton = new QPushButton(controlsFrame);
	exitButton->setObjectName("exitButton");
	QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
	sizePolicy.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	exitButton->setSizePolicy(sizePolicy);
	exitButton->setMinimumSize(QSize(150, 0));
	exitButton->setText(obs_module_text("Exit"));

	buttonsVLayout->insertWidget(buttonsVLayout->count() - 1, exitButton);

	QObject::connect(exitButton, &QPushButton::clicked, [mainWindow]() { mainWindow->close(); });
}

bool obs_module_load(void)
{
	blog(LOG_INFO, "[exit-button-plugin] plugin loaded");
	plugin_main();
	return true;
}

void obs_module_unload(void)
{
	blog(LOG_INFO, "[exit-button-plugin] plugin unloaded");
}

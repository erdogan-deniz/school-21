/**
 * @file filesbrows.h
 * @brief File-system browser widget — opens a folder picker and emits
 *        the parsed @ref obj_data via `objFile` when a `.obj` file is
 *        double-clicked.
 */

#ifndef FILESBROWS_H
#define FILESBROWS_H

#include <QDir>
#include <QFileSystemModel>
#include <QWidget>

#include "miwidget.h"

namespace Ui {
class FilesBrows;
}

/**
 * @brief Embedded file browser used by @ref MainWindow.
 *
 * Wraps a `QFileSystemModel` + `QListView` and dispatches
 * double-click events through @ref pathToFile (`miwidget`) so the
 * file gets parsed before being broadcast to listeners.
 */
class FilesBrows : public QWidget {
  Q_OBJECT

 public:
  explicit FilesBrows(QWidget *parent = nullptr);
  ~FilesBrows();

 public slots:
  /** @brief Double-click handler — parse the selected file and emit signals. */
  void on_listView_doubleClicked(const QModelIndex &index);

 signals:
  /** @brief Emitted with the absolute path of the chosen file. */
  void nameChanged(const QString &);
  /** @brief Emitted with the parsed model data. */
  void objFile(obj_data);

 private:
  Ui::FilesBrows *ui;

  QFileSystemModel *model;  ///< Model backing the list view.

  miwidget pathToFile;       ///< Helper owning the parser entry point.
};

#endif  // FILESBROWS_H

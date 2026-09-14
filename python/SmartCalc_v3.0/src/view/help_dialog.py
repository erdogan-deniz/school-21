"""Help dialog: describes the interface and supported operations."""

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import (
    QDialog,
    QDialogButtonBox,
    QLabel,
    QVBoxLayout,
    QWidget,
)


_HELP_TEXT = """
<h2>SmartCalc v3.0 — Справка</h2>

<h3>Калькулятор</h3>
<p>Введите выражение в поле ввода и нажмите <b>=</b> для вычисления.</p>
<p>Поддерживаемые операции:</p>
<ul>
  <li><b>+</b> Сложение, <b>-</b> Вычитание</li>
  <li><b>*</b> Умножение, <b>/</b> Деление</li>
  <li><b>^</b> Степень (например, 2^10)</li>
  <li><b>mod</b> Остаток от деления (например, 10 mod 3)</li>
  <li><b>Унарный минус</b>: -x, -(5+3)</li>
</ul>
<p>Математические функции: <b>sin</b>, <b>cos</b>, <b>tan</b>,
<b>asin</b>, <b>acos</b>, <b>atan</b>, <b>sqrt</b>, <b>ln</b>, <b>log</b></p>
<p>Переменная <b>x</b>: введите значение x в поле
«Значение x» перед вычислением.</p>
<p>Максимальная длина выражения: 255 символов.</p>
<p>Точность результата: 7 знаков.</p>

<h3>График функции</h3>
<p>Введите выражение с переменной <b>x</b>,
задайте диапазоны и нажмите <b>Построить</b>.</p>
<p>Диапазон значений: от -1 000 000 до 1 000 000.</p>

<h3>История</h3>
<p>Каждое вычисление сохраняется автоматически.</p>
<p>Двойной клик на запись загружает выражение в поле ввода.</p>
<p>Кнопка «Очистить» удаляет всю историю.</p>

<h3>Кредитный калькулятор</h3>
<p>Введите сумму кредита, срок (в месяцах), ставку (% годовых) и тип выплат.</p>
<ul>
  <li><b>Аннуитет</b> — равные ежемесячные платежи</li>
  <li><b>Дифференцированный</b> — убывающие платежи</li>
</ul>

<h3>Депозитный калькулятор</h3>
<p>Введите сумму депозита, срок, ставку,
налоговую ставку и параметры выплат.</p>
<p>При включённой капитализации проценты добавляются к телу депозита.</p>

<h3>Настройки (config.ini)</h3>
<ul>
  <li><b>theme</b> — тема оформления: light или dark</li>
  <li><b>font_size</b> — размер шрифта (пункты)</li>
  <li><b>precision</b> — количество значимых цифр в результате</li>
  <li><b>rotation_period</b> — период ротации логов: hour, day, month</li>
</ul>
"""


class HelpDialog(QDialog):
    """Modal dialog showing the application help text."""

    def __init__(self, parent: QWidget | None = None) -> None:
        """Create and lay out the help dialog.

        Args:
            parent: Optional parent widget.

        """
        super().__init__(parent)
        self.setWindowTitle("Справка — SmartCalc v3.0")
        self.setMinimumSize(550, 500)

        layout = QVBoxLayout(self)

        label = QLabel(_HELP_TEXT)
        label.setWordWrap(True)
        label.setAlignment(Qt.AlignmentFlag.AlignTop)
        label.setTextFormat(Qt.TextFormat.RichText)
        layout.addWidget(label)

        buttons = QDialogButtonBox(QDialogButtonBox.StandardButton.Ok)
        buttons.accepted.connect(self.accept)
        layout.addWidget(buttons)

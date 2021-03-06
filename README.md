# Инструкция по использованию клиента ведущего

## Подготовка пакета.
Предварительно необходимо отформатировать пакет под использование программой. Пакет может быть сохранён только в формате txt. Разметка похожа на стандартное оформление, но есть некие обязательные моменты, на которые стоит обратить внимание:
 - список зарезервированных ключевых слов: "Тема", "10", "20", "30", "40", "50", "Ответ", "Комментарий". Всё, что начинается с этих слов, программа воспринимает как соответствующий элемент темы. Ничто другое так начинаться не может, следите за абзацами.
 - Перед первой темой может быть написано всё, что угодно, кроме вышеперечисленных ограничений.
 - Тема должна быть оформлена по шаблону

```Тема ...
Комментарий (опциоанально)
10.
Ответ:
(опциональные поля "Зачёт", "Комментарий", "Источник" и "Автор")
20.
Ответ:
(опциональные поля "Зачёт", "Комментарий", "Источник" и "Автор")
30.
Ответ:
(опциональные поля "Зачёт", "Комментарий", "Источник" и "Автор")
40.
Ответ:
(опциональные поля "Зачёт", "Комментарий", "Источник" и "Автор")
50.
Ответ:
(опциональные поля "Зачёт", "Комментарий", "Источник" и "Автор")
```

наличие пустых строк не влияет на программу никак. Обратите внимание на порядок вопросов. Если в теме окажутся перепутаны номиналы или будет, скажем, 2 вопроса за 20, программа это не съест.

## Перед игрой
 - зайдите в меню "Настройки"
 - выберите пакет
 - задайте имена игроков (их может быть не более четырёх)
 - установите или отключите лимит на количество апелляций для каждого игрока. Если лимит установлен, то задайте его числовое значение. При каждой удовлетворённой апелляции лимит не расходуется.
 - если выбрать пункт "Показывать ответы вместе с вопросами", то ведущий будет сразу видеть тексты и вопросов, и ответов. Такой расклад не требует детального знания ответов, но есть риск случано вместе с вопросом прочитать ответ.
 - задайте время на обдумывание вопроса. От 5 до 10 секунд.
 - для онлайн-игры можно включить переотбивки и фальстарты
 - после нажатия кнопки "Применить" появятся настройки сервера, если вы выбрали онлайн-игру. Задайте номер порта на ваш выбор от 2000 до 65535.
 - в онлайн-игре можно сделать сдачу ответов письменной
 - перестрелка когда-нибудь будет, но пока эти галочки просто для красоты.

## Ход игры
 - нажмите кнопку "Начать игру"
 - нажимайте "Далее" после показа преамбулы, после установки темы, после показа вопроса, после показа ответа на вопрос
 - если вы хотите доверить отсчёт времени автоматике, то после окончания чтения вопроса и после каждого неверного ответа (если вопрос дочитан) нажимайте кнопку запуска таймера.
 - если игрок дал верный ответ, нажмите "+" под его именем, если неверный, то нажмите "-". Обратите внимание, что нажать "+" или "-" можно только до того, как вы выведете на экран правильный ответ.
 - если игрок подал апелляцию, то нажмите кнопку "Апелляция". Выберите тип апелляции "зачёт/снятие" и номер игрока, который её подал. Затем нажмите на кнопку с вердиктом ("Принять" или "Отклонить")


## Завершение игры
 - по окончании розыгрыша всех вопросов нажмите на кнопку "Завершить игру".
 - в открывшемся окне выберите место сохранения отчёта об игре"
 - закройте появившееся окно "Игра успешно завершена".


##  Исправление технических ошибок во время ведения.
- вы поставили "+" игроку №1, а должны были игроку №2. Поставьте "+" игроку №2 и подайте апелляцию на зачёт ответа игроку №2. Лишние баллы игрока №1 сбросятся.
- вы поставили "-" игроку №1, а должны были ему поставить "+". Подайте апелляцию на зачёт ответа игроку №1
- вы поставили "-" ироку №1, а должны были игроку №2. Пока эта проблема решается только снятием вопроса. Над решением думаем.
- вы поставили "+" игроку №1, а должны были ему же поставить "-". Подайте апелляцию на незачёт ответа игроку №1

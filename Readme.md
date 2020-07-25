# Simple Logger Lib

Простая библиотека для логирования. 
Умеет записывать логи как в cout/cerr, так и в файл.

#### Как использовать:
1) Подключите в ваш класс `Logger.hpp`
2) Добавьте в ваш класс переменную типа `LoggerInstance`. В конструкторе инициализируйте её строкой - префиксом для лога (логи из этого класса будут префиксоваться данной строкой)
3) Используйте методы DebugLog() и ErrorLog() для записи информации и ошибок соответственно     

#### Как подключить:
В вашем основном Cmake-файле добавьте следующие строчки:
`````
add_subdirectory(Sources/Logger)
target_link_libraries(*название_вашего_проекта* Logger)
````` 
Внимание! Используется библиотека boost. Если у вас её нет - необходимо установить [по ссылке](https://www.boost.org/users/download/), или из своего пакетного менеджера `libboost-system-dev` и `libboost-date-time-dev`

---

Пример лога:

`2020-Jul-25 14:45:01: [Core] Initialized`

где 
- `2020-Jul-25 14:45:01` - текущие дата и время
- `Core` - префикс класса, переданный в конструкторе
- `Initialized` - сообщение 


---

###### Настройки (env)

| Переменная          | Значения             | По умолчанию |
| ------------------- | :------------------: | :----------: |
| $SWS_LOG_TARGET | `File` (Логгирует в файл log.txt), <br> `OutputStream` (выводит логи в cout/cerr) | `File` |

--- 
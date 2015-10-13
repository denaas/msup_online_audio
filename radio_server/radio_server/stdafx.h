// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <winsock.h> // здесь наход§тс§ заголовки функций сокетов
#include <iostream>
#include <string> 

#pragma comment(lib, "wsock32.lib") // добавл§ем библиотеку дл§ функций сокетов

#define SOCKMAXCONN 20

// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы

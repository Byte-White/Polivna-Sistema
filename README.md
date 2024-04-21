# Тема: Система за автоматично поливане на растения


Изговили: Христо Милев, Александра Атанасова, Александър Язаджиев, Теодор Пенков ученици в 11 клас МГ “Академик Кирил Попов“, гр. Пловдив


## Съдържание: 
1.	Описание на проекта.
2.	Блокова схема.
3.	Електрическа схема.
4.	Списък съставни части.
5.	Сорс код.
6.	Заключение.
   
Описание: 

Този проект представлява система за автоматично поливане на растения, която използва Arduino и различни сензори за контрол на влажността на почвата, температурата и нивото на осветеност около растенията.
Основната цел на проекта е да се създаде умна система, която може да поддържа оптималните условия за растеж на растенията без непрекъснатото присъствие на човек. Проектът се състои от следните ключови компоненти:

1.	Сензор за температура: Измерва температурата около растенията, което е важно за определянето на оптималните условия за растеж.
2.	Фоторезистор: Измерва нивото на осветеност около растенията, което може да определи дали е ден или нощ.
3.	Сензор за влажност на почвата: Измерва влажността на почвата около растенията, което позволява на системата да регулира поливането според нуждите на растенията.
4.	Бутони за управление: Позволяват на потребителя да избира различни настройки и режими на системата, като например нивото на влажност, период на поливане и други.
5.	Система за поливане: Управлява актуатора, който осигурява вода на растенията според измерените параметри от сензорите и настройките на потребителя.
6.	LCD дисплей: Показва текущата информация за температурата, нивото на осветеност, влажността на почвата и други важни данни. Също така позволява на потребителя да взаимодейства с системата и да извършва настройки.

Целта на този проект е да се създаде интелигентна и ефективна система за поддръжка на растения, която може да работи автономно и да осигурява оптимални условия за тяхния растеж и развитие.





Блокова система:

![screenshot](https://github.com/Byte-White/Polivna-Sistema/blob/main/screenshot.png) 

[Tinkercad simulation](https://www.tinkercad.com/things/4BtUAD0HUp2-polivna-sistema-it-kariera?sharecode=EqKPJBGXpywZkfToVlrN17EBJvYNN6NRyFf4zADJAkQ)



Електрическа система: 

![scheme](https://github.com/Byte-White/Polivna-Sistema/assets/51212450/cf83baa9-8d86-4b24-845c-9713cdf8c4bd)
 

Списък съставни части: 

1.	Arduino - Микроконтролерната платформа, която изпълнява програмата и контролира външните компоненти.
2.	Сензор за температура - Използва се за измерване на температурата около растенията.
3.	Фоторезистор - Използва се за измерване на нивото на осветеност около растенията.
4.	Сензор за влажност на почвата - Използва се за измерване на влажността на почвата около растенията.
5.	Бутони за управление - Използват се за превключване между различните режими на програмата и настройки.
6.	Система за поливане - Използва се за автоматично поливане на растенията според измерените параметри от сензорите. (В симулацията е LED лампичка). 
7.	LCD дисплей - Използва се за показване на информацията за температурата, нивото на осветеност и влажността на почвата, както и за настройка на програмата чрез бутоните.
Тези компоненти са свързани помежду си и с Arduino, така че програмата може да извършва измервания, взима решения и управлява системата за поливане в съответствие с измерените стойности и настройките на потребителя.


Сорс код:

Този код представлява програма за контрол на система за поливане на растения. Неколкото основни компоненти се използват в програмата:
1.	Клас за Сензор за Температура (TemperatureSensor): Този клас измерва температурата чрез аналогов сензор. Методът GetTemperature() връща измерената температура в градуси Целзий.
2.	Клас за Фоторезистор (PhotoResistor): Този клас измерва нивото на осветеност чрез аналогов сензор. Методът GetLight() връща стойността на осветеността, а GetLightLevelString() връща текстова стойност ("Слънчево", "Облачно" или "Нощ") спрямо измерената осветеност.
3.	Клас за Сензор за Влажност на Почвата (SoilMoistureSensor): Този клас измерва влажността на почвата чрез аналогов сензор. Методът CalculateMoisturePercentage() връща процентното съотношение на влажността на почвата.
4.	Клас за Бутон (Button): Този клас представлява бутон за управление. Методът IsClicked() проверява дали бутона е натиснат.
5.	Клас за Система за Поливане (WateringSystem): Този клас контролира системата за поливане. Методите TurnOn() и TurnOff() включват и изключват системата съответно.
6.	Главна функция (loop()): В тази функция се извършва основната логика на програмата. Тя се изпълнява непрекъснато в цикъл. В зависимост от текущо избраната разделна вкладка (Main, MoistureLevel или DayTime), се извикват съответните функции за изобразяване на информация на LCD дисплея.
7.	Функция за проверка на необходимост от поливане (waterIfNeeded()): Тази функция се извиква от loop() и проверява дали е необходимо поливане спрямо текущите условия (избрана влажност на почвата и ден/нощ). Ако са изпълнени условията за поливане, се включва системата за поливане чрез метода TurnOn() на обекта от класа WateringSystem. В противен случай системата се изключва чрез метода TurnOff().
В setup() функцията се инициализират всички компоненти и настройва LCD дисплея.


Заключение:

В заключение, този проект представлява интелигентна система за автоматично поливане на растения, която използва Arduino и различни сензори за контрол на влажността на почвата, температурата и нивото на осветеност около растенията. Чрез използването на тези сензори и актуатори, системата може да реагира на текущите условия в околната среда и да осигури оптималните условия за растеж на растенията без непрекъснато присъствие на човек.
Този проект е полезен за хората, които се интересуват от ботаниката и отглеждането на растения, но нямат достатъчно време или възможност да се грижат за тях ежедневно. Системата предлага автоматизирано и ефективно решение за поддръжка на растенията, като същевременно позволява на потребителя да контролира и настройва различни аспекти на системата според конкретните нужди на растенията и предпочитанията на потребителя.
В крайна сметка, този проект допринася за оптимизиране на процеса на отглеждане на растения и за създаване на здравословна и устойчива среда за тяхното растеж и развитие.


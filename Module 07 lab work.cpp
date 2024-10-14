#include <iostream>
#include <memory>
#include <stdexcept>

// Интерфейс стратегии доставки
class IShippingStrategy {
public:
    virtual ~IShippingStrategy() = default;
    virtual double CalculateShippingCost(double weight, double distance) const = 0;
};

// Стратегия стандариной доставки
class StandardShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return weight * 0.5 + distance * 0.1;
    }
};

// Стратегия экспресс-доставки
class ExpressShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return (weight * 0.75 + distance * 0.2) + 10; // Дополнительная плата за скорость
    }
};

// Стратегия международной доставки
class InternationalShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return weight * 1.0 + distance * 0.5 + 15; // Доп сборы за международную доставку
    }
};

// Стратегия ночной доставки
class NightShippingStrategy : public IShippingStrategy {
public:
    double CalculateShippingCost(double weight, double distance) const override {
        return weight * 0.75 + distance * 0.2 + 20; // Фикс плата за срочность
    }
};

// Контекст, использующий стратегию для расчета стоимости доставки
class DeliveryContext {
private:
    IShippingStrategy* strategy = nullptr;

public:
    void SetShippingStrategy(IShippingStrategy* newStrategy) {
        strategy = newStrategy;
    }

    double CalculateCost(double weight, double distance) const {
        if (strategy == nullptr) {
            throw std::runtime_error("Стратегия доставки не установлена.");
        }
        return strategy->CalculateShippingCost(weight, distance);
    }
};

// Главный метод программы
int main() {
    DeliveryContext deliveryContext;

    std::cout << "Выберите тип доставки: 1 - Стандартная, 2 - Экспресс, 3 - Международная, 4 - Ночная\n";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            deliveryContext.SetShippingStrategy(new StandardShippingStrategy());
            break;
        case 2:
            deliveryContext.SetShippingStrategy(new ExpressShippingStrategy());
            break;
        case 3:
            deliveryContext.SetShippingStrategy(new InternationalShippingStrategy());
            break;
        case 4:
            deliveryContext.SetShippingStrategy(new NightShippingStrategy());
            break;
        default:
            std::cout << "Неверный выбор.\n";
            return 1;
    }

    std::cout << "Введите вес посылки (в кг): ";
    double weight;
    std::cin >> weight;
    if (weight < 0) {
        std::cerr << "Ошибка: Вес должен быть положительным числом.\n";
        return 1;
    }

    std::cout << "Введите расстояние доставки (км): ";
    double distance;
    std::cin >> distance;
    if (distance < 0) {
        std::cerr << "Ошибка: Расстояние должно быть положительным числом.\n";
        return 1;
    }

    try {
        double cost = deliveryContext.CalculateCost(weight, distance);
        std::cout << "Стоимость доставки: " << cost << " доллара.\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}

/*

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Интерфейс наблюдателя
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void Update(float temperature) = 0;
};

// Интерфейс субъекта (метеостанции)
class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void RegisterObserver(IObserver* observer) = 0;
    virtual void RemoveObserver(IObserver* observer) = 0;
    virtual void NotifyObservers() = 0;
};

// Реализация метеостанции (субъект)
class WeatherStation : public ISubject {
private:
    std::vector<IObserver*> observers;
    float temperature;

public:
    // Регистрация наблюдателя
    void RegisterObserver(IObserver* observer) override {
        observers.push_back(observer);
    }

    // Его удаление
    void RemoveObserver(IObserver* observer) override {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Уведомление всех наблюдателей об изменении температуры
    void NotifyObservers() override {
        for (auto observer : observers) {
            observer->Update(temperature);
        }
    }

    // Изменение температуры и уведомление
    void SetTemperature(float newTemperature) {
        std::cout << "Изменение температуры: " << newTemperature << "°C\n";
        temperature = newTemperature;
        NotifyObservers();
    }
};

// Реализация наблюдателя (дисплей температуры)
class WeatherDisplay : public IObserver {
private:
    std::string name;

public:
    WeatherDisplay(const std::string& displayName) : name(displayName) {}

    // Получение обновления температуры
    void Update(float temperature) override {
        std::cout << name << " показывает новую температуру: " << temperature << "°C\n";
    }
};

// Доп наблюдатель Email-оповещение
class EmailAlert : public IObserver {
public:
    void Update(float temperature) override {
        std::cout << "Email-уведомление: Температура изменилась на " << temperature << "°C\n";
    }
};

// Главный метод программы
int main() {
    // Создание метеостанции
    WeatherStation weatherStation;

    // Создание нескольких наблюдателей
    WeatherDisplay mobileApp("Мобильное приложение");
    WeatherDisplay digitalBillboard("Электронное табло");
    EmailAlert emailAlert;

    // Регистрация наблюдателей
    weatherStation.RegisterObserver(&mobileApp);
    weatherStation.RegisterObserver(&digitalBillboard);
    weatherStation.RegisterObserver(&emailAlert);

    // Изменение температуры на станции и уведомление наблюдателей
    weatherStation.SetTemperature(25.0f);
    weatherStation.SetTemperature(30.0f);

    // Удаление одного табла и смена температуры
    weatherStation.RemoveObserver(&digitalBillboard);
    weatherStation.SetTemperature(28.0f);

    return 0;
}

*/





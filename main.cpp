#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

enum AlarmType { FIRE = 1, SECURITY_BREACH, LOW_BATTERY };

struct Alarm {
    AlarmType type;
    int priority;  // Lower number means higher priority
    std::string description;

    Alarm(AlarmType t, int p, const std::string& desc)
        : type(t), priority(p), description(desc) {}
};

bool operator<(const Alarm& a1, const Alarm& a2) {
    return a1.priority > a2.priority;  // Lower priority number is more urgent
}

std::priority_queue<Alarm> alarmQueue;  // Queue to manage alarms based on priority

void triggerAlarm(Alarm alarm) {
    std::cout << "Interrupt triggered: " << alarm.description << std::endl;
    alarmQueue.push(alarm);  // Add the alarm to the queue
}

void processAlarms() {
    while (!alarmQueue.empty()) {
        Alarm currentAlarm = alarmQueue.top();
        alarmQueue.pop();  // Remove the top alarm from the queue

        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simulate delay in processing
        std::cout << "Processing " << currentAlarm.description << " with priority " << currentAlarm.priority << std::endl;
    }
}

void simulateAlarms() {
    std::cout << "Starting alarm simulation...\n";

    // Simulate triggering alarms
    triggerAlarm(Alarm(FIRE, 1, "Fire detected in the building"));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    triggerAlarm(Alarm(SECURITY_BREACH, 2, "Security breach detected at the entrance"));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    triggerAlarm(Alarm(LOW_BATTERY, 3, "Low battery detected in system"));

    // Process alarms based on priority
    processAlarms();
}

int main() {
    simulateAlarms();  // Simulate the alarm events
    return 0;
}

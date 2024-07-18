#include <Arduino_FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Define the directions and car structure
typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef struct {
    int id;
    Direction from;
    Direction to;
    int proximity; // Proximity to intersection: lower value means closer
} Car;

// Queue handle for car arrivals
QueueHandle_t carQueue;

// Mutex for controlling the intersection
SemaphoreHandle_t intersectionMutex;

// Task priorities
#define PRIORITY_CAR_ARRIVAL 2
#define PRIORITY_INTERSECTION 1

// Function to simulate cars arriving from a direction
void carArrivalTask(void *pvParameters) {
    Direction dir = *((Direction *)pvParameters);
    static int carID = 0;

    while (1) {
        Car car;
        car.id = carID++;
        car.from = dir;
        car.to = (Direction)(random(0, 4)); // Randomly choose the direction to go
        car.proximity = random(1, 11); // Proximity between 1 and 10

        // Simulate car arriving
        if (xQueueSend(carQueue, &car, portMAX_DELAY) != pdPASS) {
            Serial.println("Failed to send to queue.");
        }

        // Print a message to the serial monitor
        Serial.print("Car from ");
        switch (dir) {
            case NORTH: Serial.print("NORTH"); break;
            case SOUTH: Serial.print("SOUTH"); break;
            case EAST: Serial.print("EAST"); break;
            case WEST: Serial.print("WEST"); break;
        }
        Serial.print(" with ID ");
        Serial.print(car.id);
        Serial.print(" wants to go to ");
        switch (car.to) {
            case NORTH: Serial.print("NORTH"); break;
            case SOUTH: Serial.print("SOUTH"); break;
            case EAST: Serial.print("EAST"); break;
            case WEST: Serial.print("WEST"); break;
        }
        Serial.print(" with proximity ");
        Serial.println(car.proximity);

        // Wait for some time before the next car arrives
        vTaskDelay(pdMS_TO_TICKS(1000 + random(0, 1000))); // Variable delay
    }
}

// Function to manage the intersection
void intersectionTask(void *pvParameters) {
    Car car;

    while (1) {
        // Try to take the mutex to control the intersection
        if (xSemaphoreTake(intersectionMutex, portMAX_DELAY) == pdTRUE) {
            // Check if there are cars waiting
            if (uxQueueMessagesWaiting(carQueue) > 0) {
                // Prioritize the car closest to the intersection
                Car closestCar;
                closestCar.proximity = 11; // Higher than max proximity
                int queueSize = uxQueueMessagesWaiting(carQueue);

                for (int i = 0; i < queueSize; i++) {
                    if (xQueueReceive(carQueue, &car, portMAX_DELAY) == pdPASS) {
                        if (car.proximity < closestCar.proximity) {
                            // Put the previous closest car back to the queue
                            if (closestCar.proximity != 11) {
                                xQueueSend(carQueue, &closestCar, portMAX_DELAY);
                            }
                            closestCar = car;
                        } else {
                            xQueueSend(carQueue, &car, portMAX_DELAY);
                        }
                    } else {
                        Serial.println("Failed to receive from queue.");
                    }
                }

                // Handle conflicts and prioritize
                Serial.print("Priority given to car from ");
                switch (closestCar.from) {
                    case NORTH: Serial.print("NORTH"); break;
                    case SOUTH: Serial.print("SOUTH"); break;
                    case EAST: Serial.print("EAST"); break;
                    case WEST: Serial.print("WEST"); break;
                }
                Serial.print(" with ID ");
                Serial.print(closestCar.id);
                Serial.print(" to go to ");
                switch (closestCar.to) {
                    case NORTH: Serial.print("NORTH"); break;
                    case SOUTH: Serial.print("SOUTH"); break;
                    case EAST: Serial.print("EAST"); break;
                    case WEST: Serial.print("WEST"); break;
                }
                Serial.println(" due to higher proximity.");
                
                // Introduce a small delay to simulate conflict resolution time
                vTaskDelay(pdMS_TO_TICKS(500));

                // Process the car closest to the intersection
                Serial.print("Car from ");
                switch (closestCar.from) {
                    case NORTH: Serial.print("NORTH"); break;
                    case SOUTH: Serial.print("SOUTH"); break;
                    case EAST: Serial.print("EAST"); break;
                    case WEST: Serial.print("WEST"); break;
                }
                Serial.print(" with ID ");
                Serial.print(closestCar.id);
                Serial.print(" is passing through to ");
                switch (closestCar.to) {
                    case NORTH: Serial.print("NORTH"); break;
                    case SOUTH: Serial.print("SOUTH"); break;
                    case EAST: Serial.print("EAST"); break;
                    case WEST: Serial.print("WEST"); break;
                }
                Serial.println(".");

                // Simulate the car passing through the intersection
                vTaskDelay(pdMS_TO_TICKS(1000));

                // Print completion message
                Serial.print("Car with ID ");
                Serial.print(closestCar.id);
                Serial.println(" has passed through the intersection.");
            } else {
                Serial.println("No cars waiting in the queue.");
            }

            // Release the mutex
            xSemaphoreGive(intersectionMutex);
        } else {
            Serial.println("Failed to take mutex.");
        }

        // Wait a little before checking the queues again
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void setup() {
    // Initialize serial communication
    Serial.begin(9600);
    while (!Serial) {
        ; // Wait for serial port to connect. Needed for native USB port only
    }

    Serial.println("Starting intersection control system...");

    // Initialize the queue
    carQueue = xQueueCreate(20, sizeof(Car));

    // Check if the queue was created successfully
    if (carQueue == NULL) {
        Serial.println("Queue creation failed!");
        while (1); // Halt the system
    }

    // Initialize the mutex
    intersectionMutex = xSemaphoreCreateMutex();

    // Check if the mutex was created successfully
    if (intersectionMutex == NULL) {
        Serial.println("Mutex creation failed!");
        while (1); // Halt the system
    }

    // Define directions
    Direction north = NORTH;
    Direction south = SOUTH;
    Direction east = EAST;
    Direction west = WEST;

    // Create tasks for car arrival
    xTaskCreate(carArrivalTask, "NorthArrival", 512, (void *)&north, PRIORITY_CAR_ARRIVAL, NULL);
    xTaskCreate(carArrivalTask, "SouthArrival", 512, (void *)&south, PRIORITY_CAR_ARRIVAL, NULL);
    xTaskCreate(carArrivalTask, "EastArrival", 512, (void *)&east, PRIORITY_CAR_ARRIVAL, NULL);
    xTaskCreate(carArrivalTask, "WestArrival", 512, (void *)&west, PRIORITY_CAR_ARRIVAL, NULL);

    // Create the intersection management task
    xTaskCreate(intersectionTask, "Intersection", 512, NULL, PRIORITY_INTERSECTION, NULL);

    // Start the scheduler
    vTaskStartScheduler();
}

void loop() {
    // Do nothing here
    // Tasks are managed by the FreeRTOS scheduler
}

// Hook function for stack overflow
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // Handle stack overflow
    Serial.print("Stack overflow in task: ");
    Serial.println(pcTaskName);
    while (1);
}

// Hook function for malloc failure
void vApplicationMallocFailedHook() {
    // Handle malloc failure
    Serial.println("Malloc failed.");
    while (1);
}

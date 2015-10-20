#ifndef SERVICE_MANAGER_SERVICEMANAGER_H
#define SERVICE_MANAGER_SERVICEMANAGER_H

#include <memory>
#include <thread>
#include <vector>
#include <Settings.h>

class service_manager;

/**
 * @brief The service class.
 * Abstract service for service_manager.
 */
class service {
public:
    /**
     * Configure this service.
     * @param settings service configuration
     * @param manager service_manager in which this service will work.
     */
    virtual void setup(std::shared_ptr<settings> const & settings,
                       std::shared_ptr<service_manager> const & manager) = 0;

    /**
     * Run this task.
     */
    virtual void run() = 0;

    /**
     * Stop this task.
     */
    virtual void shutdown() = 0;
};

/**
 * @brief The service_manager class.
 * Class service_manager can manage inherits of service and void functions without arguments.
 */
class service_manager : public std::enable_shared_from_this<service_manager> {
public:
    /**
     * @brief Constructor.
     * Construct and configure service manager.
     * @param my_settings
     */
    service_manager(std::shared_ptr<settings> const & my_settings);

    /**
     * @brief Destructor.
     * It calls shutdown() and destroy this service_manager.
     */
    ~service_manager();

    /**
     * If service_manager is started it add service to list and call service::run() in new thread,
     * else it only add service to list.
     * @param new_service service to run.
     */
    void run_service(std::shared_ptr<service> const & new_service);

    /**
     * It starting service manager and run all services from list.
     * If service manager is already started does nothing.
     */
    void start();

    /**
     * It shutdowns all services and breaks all tasks.
     * If service manager isn't started yet does nothing.
     */
    void shutdown();

    /**
     * Run given task in new thread if it possible.
     * @param task task to run
     * @throw BusyThreads
     * @throw NotStarted
     */
    void run_task(std::function<void()> const & task);

    /**
     * Set new amount of threans in which you can run the task.
     * It doesn't affect to services
     * @param count
     */
    void set_num_threads(size_t count);

    /**
     * Save current configuration to disk.
     */
    void save_config();

    //Bonus
//    template<typename T>
//    void register_service(std::string const & name);

//    void add_startup_service(std::string const & name);
//    void remove_startup_service(std::string const & name);

};
#endif //SERVICE_MANAGER_SERVICEMANAGER_H

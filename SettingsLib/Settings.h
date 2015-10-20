#ifndef SETTINGSLIB_SETTINGS_H
#define SETTINGSLIB_SETTINGS_H

#include <iostream>
#include <string>
#include <map>

class settings {
private:
    std::string name;
    std::map <std::string, std::string> st;
    void save();
public:
    class param {
    private:
        param(param const &);

    public:
        operator std::string() const;

        operator int() const;

        operator bool() const;

        operator double() const;

        param &operator=(std::string const &);

        param &operator=(int);

        param &operator=(bool);

        param &operator=(double);

        param &operator+=(std::string const &);

        param &operator+=(int);

        param &operator+=(double);

        param &operator-=(int);

        param &operator-=(double);

        param &operator*=(int);

        param &operator*=(double);

        param &operator/=(int);

        param &operator/=(double);

        param &operator|=(bool);

        param &operator&=(bool);

        bool is_empty() const;
    };

    // Main functions

    /**
     * Construct settings store
     * and load data from file (if exists)
     * \param filename Path to file with settings
     */
    settings(std::string const &filename);

    /**
     * Get setting value
     * \param name Setting unique identifier
     * \param def Default setting value
     * \return Stored value for given name or default value
     */
    std::string const &get(std::string const &name,
                           std::string const &def = "") const;

    /**
     * Set or replace setting value and save changes to file
     * \param name Setting unique identifier
     * \param value New setting value
     */
    void set(std::string const &name,
             std::string const &value);

    /**
     * Reset all settings
     */
    void reset();

    /**
     * Reload all settings from file
     */
    void reload();

    // Advanced fun�tions

    /**
      * Get constant setting wrapper
      * \param name Setting unique identifier
      */
    const param operator[](std::string const &name) const;

    /**
      * Get constant setting wrapper
      * \param name Setting unique identifier
      */
    param operator[](std::string const &name);
};

#endif //SETTINGSLIB_SETTINGS_H
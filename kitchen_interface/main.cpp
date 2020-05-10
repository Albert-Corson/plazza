/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** main
*/

#include "locateKitchenBin.hpp"
#include "KitchenInterface.hpp"

int main(int argc, char const *argv[])
{
    updateKitchenBinLocation();
    try {
        KitchenInterface interface(argc > 1 ? argv[1] : "");
        interface.start();
    } catch (const std::exception &err) {
        std::cerr << "Kitchen interface fatal error:" << std::endl
                  << "\t" << err.what() << std::endl;
        return (1);
    } catch (...) {
        std::cerr << "Kitchen interface fatal error" << std::endl;
        return (1);
    }
    return (0);
}

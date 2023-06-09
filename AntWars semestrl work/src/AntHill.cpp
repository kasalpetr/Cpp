#include "AntHill.hpp"

AntHill::AntHill() {}

AntHill::AntHill(int id, int x, int y)
    : id(id)
{
    position.setX(x);
    position.setY(y);
    if (id == 0)
    {
        Owner = 1;
    }
    if (id == 1)
    {
        Owner = 2;
    }
}

void AntHill::ProduceAnts()
{
    number_of_ants = number_of_ants + production;
    if (number_of_ants > max_ants)
    {
        number_of_ants = max_ants;
    }
}

Position AntHill::getPosition() const
{
    return position;
}

int AntHill::getId() const
{
    return id;
}

int AntHill::getOwner() const
{
    return Owner;
}

int AntHill::getNumberOfAnts() const
{
    return number_of_ants;
}

int AntHill::getMaxNumberOfAnts() const
{
    return max_ants;
}

int AntHill::getAttack() const
{
    return attack;
}

int AntHill::getDefend() const
{
    return defend;
}

int AntHill::getlevel() const
{
    return level;
}

void AntHill::setLevel()
{
    level++;
}

void AntHill::setMaxAnts()
{
    max_ants = max_ants + 25;
}

void AntHill::setdefend()
{
    defend = defend + 10;
}

void AntHill::setattack()
{
    attack = attack + 10;
}

void AntHill::loadnewAntHills(int _id, int _level, int _number_of_ants, int _max_of_ants, int _owner, int _attack, int _defend)
{
    id = _id;
    level = _level;
    number_of_ants = _number_of_ants;
    max_ants = _max_of_ants;
    Owner = _owner;
    attack = _attack;
    defend = _defend;
}

void AntHill::setproduction()
{
    production = production + 10;
}

void AntHill::print()
{
    if (Owner == 1) // hrac
    {
        cout << "\x1B[42m" << id; // Escape sekvence pro nastavení zeleného pozadí
        cout << "\x1B[0m";        // Resetování barev
    }
    else if (Owner == 2) // pc
    {
        cout << "\x1B[44m" << id; // Escape sekvence pro nastavení modrého pozadí
        cout << "\x1B[0m";        // Resetování barev
    }
    else
    {
        // nikdo
        cout << "\x1B[41m" << id; // Escape sekvence pro nastavení červeného pozadí
        cout << "\x1B[0m";        // Resetování barev
    }
}

bool AntHill::IsPassable() const
{
    return isPassable;
}

void AntHill::setPassable(bool pruchod)
{
    isPassable = pruchod;
}

void AntHill::changeOwner(int new_owner)
{
    Owner = new_owner;
}

bool AntHill::Attack(AntHill &Attack_from)
{
    int defense = number_of_ants * level * defend;
    int attack = Attack_from.getNumberOfAnts() * Attack_from.getlevel() * Attack_from.getAttack();

    if (defense - attack < 0)
    {
        this->number_of_ants = abs(((defense - attack) / Attack_from.getlevel()) / Attack_from.getAttack());
        Attack_from.number_of_ants = 0;
        changeOwner(Attack_from.getOwner());
        return true;
    }
    if (defense - attack > 0)
    {
        this->number_of_ants = abs(((defense - attack) / level) / defend);
        Attack_from.number_of_ants = 0;
        return false;
    }
    if (defense - attack == 0)
    {
        this->number_of_ants = 0;
        Attack_from.number_of_ants = 0;
        return false;
    }
    return false;
}

void AntHill::support(AntHill &Attack_from)
{
    number_of_ants = number_of_ants + Attack_from.getNumberOfAnts();
    Attack_from.number_of_ants = 0;
}

int AntHill::printAttackTo(const vector<AntHill> &AntsHill_onBoard)
{
    int id = -1;
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        if (anthill.getOwner() == 0 || anthill.getOwner() == 2)
        {
            cout << anthill.getId() << "-> " << anthill.getNumberOfAnts() << endl;
        }
    }
    cin >> id;
    if (std::cin.eof())
        return 0;
    if (cin.fail())
    {
        cin.clear();                                         // Vynulovat příznaky chyby u cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorovat zbylé znaky ve vstupním proudu až do konce řádku
    }
    else
    {
        for (const AntHill &anthill : AntsHill_onBoard)
        {
            if (anthill.getOwner() == 0 || anthill.getOwner() == 2)
            {
                if (id == anthill.getId())
                {
                    return id;
                }
            }
        }
    }
    cout << "Zadej správnou hodnotu" << endl;
    return printAttackTo(AntsHill_onBoard);
}

int AntHill::printSupportTo(const vector<AntHill> &AntsHill_onBoard)
{
    int id = -1;
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        if (anthill.getOwner() == 1)
        {
            cout << anthill.getId() << "-> " << anthill.getNumberOfAnts() << endl;
        }
    }
    cin >> id;
    if (std::cin.eof())
        return 0;
    if (cin.fail())
    {
        cin.clear();                                         // Vynulovat příznaky chyby u cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorovat zbylé znaky ve vstupním proudu až do konce řádku
    }
    else
    {
        for (const AntHill &anthill : AntsHill_onBoard)
        {
            if (anthill.getOwner() == 1)
            {
                if (id == anthill.getId())
                {
                    return id;
                }
            }
        }
    }
    cout << "Zadej správnou hodnotu" << endl;
    return printSupportTo(AntsHill_onBoard);
}
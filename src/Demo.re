type person = {
  age: int,
  name: string,
};
type monster = {
  age: int,
  hasTentacles: bool,
};

[@bs.deriving jsConverter]
type team = {
    size: int,
    m: monster,
    p: person,
}

let getTeamPerson = ({p}: team) => p.name;

let mixedTeam: team = { size: 3, m: { age: 1, hasTentacles: false }, p: { name: "Bob", age: 22 } }

type p =
  | Person(person);
type m =
  | Monster(monster);
/* If you delete type e, let c will fail... */
type e =
  | Person(person)
  | Monster(monster);

type army('x) =
  | Army('x, armyMembers('x))
and armyMembers('x) =
  | ArmyMembers('x);

let a =
  Army(
    Monster({age: 30, hasTentacles: true}),
    ArmyMembers(Monster({age: 12, hasTentacles: false})),
  );

let b =
  Army(
    Person({age: 30, name: "Ghengis Khan"}),
    ArmyMembers(Person({age: 12, name: "Bob"})),
  );

let c =
  Army(
    Person({age: 30, name: "Ghengis Khan"}),
    ArmyMembers(Monster({age: 12, hasTentacles: false})),
  );

let serializeTeam = ({size, m: { hasTentacles, age: monsterAge}, p: { name, age: personAge }}) => {
    "hasTentacles": hasTentacles,
    "age": monsterAge,
    "person": { "name": name, "age": personAge },
    "size": size
}

let j = Js.Dict.empty();
Js.Dict.set(j, "name", Js.Json.string("Bob"));
Js.Dict.set(j, "age", Js.Json.number(4.3));
Js.log(Js.Json.stringify(Js.Json.object_(j)));

Js.log(b);
Js.log(a);
Js.log(getTeamPerson(mixedTeam))
Js.log(serializeTeam(mixedTeam))
Js.log(teamToJs(mixedTeam))
/* Js.log(Js.Json.stringify(mixedTeam)) */
Js.log(mixedTeam)

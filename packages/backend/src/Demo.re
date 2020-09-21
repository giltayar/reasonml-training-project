Js.log("Hello, BuckleScript and Reason!");

let name = 1 + 3;

Js.log({j|The value of 1 + 3 is $(name)|j});

let data = {|
{
  "some": "json",
  "more": [1,3]
}
|};

type myJson = {
  some: string,
  more: array(int),
};

let myJson = json =>
  Json.Decode.{
    some: json |> field("some", string),
    more: json |> field("some", array(int)),
  };

let x = myJson(Json.parseOrRaise(data));


let add = [%raw {|
  function(a, b) {
    console.log("hello from raw JavaScript!");
    return a + b
  }
|}];

let z = add(4, 5);

Js.Console.log(z);
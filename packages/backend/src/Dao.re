type model = {value: int};

let fromJson = json => Json.Decode.{value: json |> field("value", int)};
let toJson = model => Json.Encode.(object_([("value", int(model.value))]));

let value = ref(0);

let increment = () => {
  value := value.contents + 1;

  value.contents;
};

let decrement = () => {
  value := value.contents - 1;

  value.contents;
};

let set = newValue => {
  value := newValue;

  value.contents;
};

let get = () => value.contents;

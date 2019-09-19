let str = React.string;
let uuidv4 = Uuid.V4.uuidv4;

type state = {items: list(Item.item)};

let initialState = {
  items: [{id: uuidv4(), title: "Buy milk", completed: false}],
};

type action =
  | AddItem(string)
  | ToggleItem(string)
  | DeleteItem(string);

let reducer = (state, action) =>
  switch (action) {
  | AddItem(text) => {items: [Item.newItem(text), ...state.items]}
  | ToggleItem(id) =>
    let items =
      List.map(
        (item: Item.item) => (
          item.id === id ? {...item, completed: !item.completed} : item: Item.item
        ),
        state.items,
      );
    {items: items};
  | DeleteItem(id) =>
    let items =
      List.filter((item: Item.item) => item.id !== id, state.items);
    {items: items};
  };

[@react.component]
let make = (~title="What to do") => {
  let ({items}, dispatch) = React.useReducer(reducer, initialState);

  let numItems = List.length(items);

  <>
    <div className="section is-tall">
      <header className="title has-text-centered"> {str(title)} </header>
      <main className="container is-tall-container">
        <div className="field">
          <Input onSubmit={text => dispatch(AddItem(text))} />
        </div>
        <ol className="box list">
          {
            List.map(
              item =>
                <Todo
                  item
                  key={item.id}
                  onToggle={() => dispatch(ToggleItem(item.id))}
                  onDelete={() => dispatch(DeleteItem(item.id))}
                  label={item.title}
                />,
              items,
            )
            |> Array.of_list
            |> React.array
          }
        </ol>
      </main>
      <footer>
        <p className="content has-text-left" />
        {numItems |> string_of_int |> str}
        {str(" items")}
      </footer>
    </div>
  </>;
};

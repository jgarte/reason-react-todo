let str = React.string;
let uuidv4 = Uuid.V4.uuidv4;

type item = {
  id: string,
  title: string,
  completed: bool,
};
type state = {items: list(item)};

type action =
  | AddItem(string)
  | ToggleItem(string)
  | DeleteItem(string);

[@react.component]
let make = (~title="What to do") => {
  let newItem = text => {id: uuidv4(), title: text, completed: false};
  let ({items}, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | AddItem(text) => {items: [newItem(text), ...state.items]}
        | ToggleItem(id) =>
          let items =
            List.map(
              item =>
                item.id === id ? {...item, completed: !item.completed} : item,
              state.items,
            );
          {items: items};
        | DeleteItem(id) =>
          let items = List.filter(item => item.id !== id, state.items);
          {items: items};
        },
      {items: [{id: uuidv4(), title: "Buy milk", completed: false}]},
    );

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
                <TodoItem
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

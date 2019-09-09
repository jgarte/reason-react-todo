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

module Input = {
  type state = string;
  [@react.component]
  let make = (~onSubmit) => {
    let (text, setText) =
      React.useReducer((_oldText, newText) => newText, "");
    ();
    let valueFromEvent = evt: string => evt->ReactEvent.Form.target##value;
    <input
      className="input is-primary is-large"
      value=text
      type_="text"
      placeholder="Write something to do"
      onChange={evt => setText(valueFromEvent(evt))}
      onKeyDown={
        evt =>
          if (ReactEvent.Keyboard.key(evt) == "Enter") {
            onSubmit(text);
            setText("");
          }
      }
    />;
  };
};

module TodoItem = {
  [@react.component]
  let make = (~item, ~onToggle, ~onDelete) =>
    <div className="list-item">
      <span
        className={item.completed ? "is-checked" : ""}
        onClick={_evt => onToggle()}>
        {str(" " ++ item.title)}
      </span>
      <button
        className="delete is-pulled-right"
        onClick={_evt => onDelete()}
      />
    </div>;
};

[@react.component]
let make = (~title="") => {
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
        <div className="box list">
          {
            List.map(
              item =>
                <TodoItem
                  key={item.id}
                  onToggle={() => dispatch(ToggleItem(item.id))}
                  onDelete={() => dispatch(DeleteItem(item.id))}
                  item
                />,
              items,
            )
            |> Array.of_list
            |> React.array
          }
        </div>
      </main>
      <footer>
        <p className="content has-text-left">
          {str(string_of_int(numItems) ++ " items")}
        </p>
      </footer>
    </div>
  </>;
};

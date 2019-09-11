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
  let make = (~item, ~label, ~onToggle, ~onDelete) => {
    let (editing, setEditing) = React.useState(() => false);
    let (value, onChange) = React.useState(() => label);
    let onCancel = _evt => setEditing(_ => false);
    let onFocus = event => ReactEvent.Focus.target(event)##select();

    React.useEffect1(
      () => {
        onChange(_ => label);
        None;
      },
      [|label|],
    );

    <li className="list-item">
      {
        if (editing) {
          <form onSubmit={_ => setEditing(_ => false)} onBlur=onCancel>
            <input
              onFocus
              onBlur=onCancel
              onChange={evt => onChange(ReactEvent.Form.target(evt)##value)}
              value
            />
          </form>;
        } else {
          <>
            <label
              className={item.completed ? "checkbox is-checked" : "checkbox"}>
              <input
                type_="checkbox"
                defaultChecked={item.completed}
                onClick={_evt => onToggle()}
              />
              {str(" ")}
              value->str
            </label>
            <span
              className="icon is-pulled-right" onClick={_evt => onDelete()}>
              <i className="fas fa-times" />
            </span>
            <span
              className="icon is-pulled-right"
              onClick={_evt => setEditing(_ => true)}>
              <i className="fas fa-pencil-alt" />
            </span>
          </>;
        }
      }
    </li>;
  };
};

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
                  key={item.id}
                  onToggle={() => dispatch(ToggleItem(item.id))}
                  onDelete={() => dispatch(DeleteItem(item.id))}
                  label={item.title}
                  item
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
        {str(string_of_int(numItems) ++ " items")}
      </footer>
    </div>
  </>;
};

let str = React.string;
let uuidv4 = Uuid.V4.uuidv4;

type item = {
  id: string,
  title: string,
  completed: bool,
};

type state = {items: list(item)};

type action =
  | AddItem;

let newItem = () => {id: uuidv4(), title: "A new title", completed: true};

module TodoItem = {
  [@react.component]
  let make = (~item) =>
    <div className="list-item">
      <label className="checkbox">
        <input type_="checkbox" checked={item.completed} />
        {str(item.title)}
      </label>
    </div>;
};

[@react.component]
let make = (~title="") => {
  let ({items}, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | AddItem => {items: [newItem(), ...state.items]}
        },
      {
        items: [
          {id: uuidv4(), title: "Write some things to do", completed: false},
        ],
      },
    );

  let numItems = List.length(items);

  <>
    <div className="section is-tall">
      <header className="title has-text-centered"> {str(title)} </header>
      <main className="container is-tall-container">
        <button
          className="button is-block is-info is-fullwidth panel"
          onClick={_evt => dispatch(AddItem)}>
          {str("Add")}
        </button>
        <div className="box list">
          {
            List.map(item => <TodoItem key={item.id} item />, items)
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

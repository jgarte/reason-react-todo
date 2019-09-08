let str = React.string;

type item = {
  title: string,
  completed: bool,
};

type state = {items: list(item)};

[@react.component]
let make = (~title="") => {
  let ({items}, dispatch) =
    React.useReducer(
      (state, action) => state,
      {items: [{title: "Write some things to do", completed: false}]},
    );

  let numItems = List.length(items);

  <>
    <div className="section is-tall">
      <header className="title has-text-centered"> {str(title)} </header>
      <main className="container is-tall-container">
        <div className="column is-4 is-offset-4">
          <div className="items"> {str("Nothing")} </div>
        </div>
      </main>
      <footer className="footer">
        <p className="content has-text-centered">
          {str(string_of_int(numItems) ++ " items")}
        </p>
      </footer>
    </div>
  </>;
};

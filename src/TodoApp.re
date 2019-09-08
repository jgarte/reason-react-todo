let str = React.string;

[@react.component]
let make = (~title="") =>
  <div className="section is-fullheight">
    <div className="container">
      <div className="title is-size-1 has-text-centered"> {str(title)} </div>
      <div className="column is-4 is-offset-4">
        <div className="box">
          <div className="app">
            <div className="items"> {str("Nothing")} </div>
          </div>
        </div>
      </div>
    </div>
  </div>;

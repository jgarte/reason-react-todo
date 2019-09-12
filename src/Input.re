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

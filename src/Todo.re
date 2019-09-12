let str = React.string;

[@react.component]
let make = (~item: Item.item, ~label, ~onToggle, ~onDelete) => {
  let (editing, setEditing) = React.useState(() => false);
  let (value, onChange) = React.useState(() => label);
  let onCancel = _evt => setEditing(_ => false);
  let onFocus = event => ReactEvent.Focus.target(event)##select();

  <li className="list-item">
    {
      if (editing) {
        <form
          onSubmit={
            evt => {
              ReactEvent.Synthetic.preventDefault(evt);
              setEditing(_ => false);
            }
          }
          onBlur=onCancel>
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
          <span className="icon is-pulled-right" onClick={_evt => onDelete()}>
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

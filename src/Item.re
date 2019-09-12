let uuidv4 = Uuid.V4.uuidv4;

type item = {
  id: string,
  title: string,
  completed: bool,
};

let newItem = text => {id: uuidv4(), title: text, completed: false};

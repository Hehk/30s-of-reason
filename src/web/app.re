type state = {search: string};

type actions =
  | ChangeSearch(string);

let reducer = (action, _state) =>
  switch action {
  | ChangeSearch(newValue) => ReasonReact.Update({search: newValue})
  };

let initialState = () => {search: ""};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState,
  reducer,
  render: ({state, send}) =>
    <Background>
      <Header />
      <PageFrame>
        <Search
          value=state.search
          onChange=(newValue => send(ChangeSearch(newValue)))
        />
        <Divider />
        <SnippetList filter=state.search />
      </PageFrame>
    </Background>
};

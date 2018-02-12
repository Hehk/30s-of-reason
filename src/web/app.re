type state = {search: string};

type actions =
  | ChangeSearch(string);

let changeSearch = send => {
  open Utils.Debounce;
  let update = make(newValue => send(ChangeSearch(newValue)), ~wait=250);
  newValue => update |> call(newValue);
};

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
        <Search onChange=(changeSearch(send)) />
        <SnippetList filter=state.search />
      </PageFrame>
    </Background>
};

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) => <Background> <Header /> <Input /> </Background>
};

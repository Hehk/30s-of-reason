open Nice;

open Utils;

open Theme;

let component = ReasonReact.statelessComponent("Header");

module Wrapper = (
  val NiceComponents.header(
        ~debugName="HeaderWrapper",
        [|
          BackgroundColor(Colors.red),
          Color(Colors.white),
          Padding(Spacing.large),
          Raw("font-size", Font.Size.large)
        |]
      )
);

module Logo = (
  val NiceComponents.div(
        ~debugName="HeaderLogo",
        [|Color(Colors.white), Raw("display", "inline"), FontWeight(Bold)|]
      )
);

module Nav = (
  val NiceComponents.ol(
        ~debugName="HeaderNav",
        [|
          Raw("list-style", "none"),
          Raw("float", "right"),
          Padding(Spacing.none),
          Margin(Spacing.none)
        |]
      )
);

module NavItem = (
  val NiceComponents.li(
        ~debugName="HeaderNavItem",
        [|Raw("float", "right"), MarginLeft(Spacing.large)|]
      )
);

module NavLink = (
  val NiceComponents.a(
        ~debugName="HeaderNavLink",
        [|Raw("color", "inherit"), TextDecorationLine(None_)|]
      )
);

let make = _children => {
  ...component,
  render: _self =>
    <Wrapper>
      <PageFrame>
        <Logo>
          <NavLink props={"href": "/"}> (str_to_ele("30s of Reason")) </NavLink>
        </Logo>
        <Nav>
          <NavItem>
            <NavLink props={"href": "https://github.com/hehk/30s-of-reason"}>
              (str_to_ele("Github"))
            </NavLink>
          </NavItem>
          <NavItem>
            <NavLink props={"href": "/about"}> (str_to_ele("About")) </NavLink>
          </NavItem>
        </Nav>
      </PageFrame>
    </Wrapper>
};

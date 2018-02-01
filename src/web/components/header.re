open Nice;

open Utils;

let component = ReasonReact.statelessComponent("Header");

module Wrapper = (
  val NiceComponents.header(
        ~debugName="HeaderWrapper",
        [BackgroundColor(RGBa(219, 77, 63, 1.)), Color(White), Padding(Px(20)), Raw("font-size", "1.25rem")]
      )
);

module Logo = (
  val NiceComponents.div(~debugName="HeaderLogo", [Color(White), Raw("display", "inline"), FontWeight(Bold)])
);

module Nav = (
  val NiceComponents.ol(
        ~debugName="HeaderNav",
        [Raw("list-style", "none"), Raw("float", "right"), Padding(Px(0)), Margin(Px(0))]
      )
);

module NavItem = (val NiceComponents.li(~debugName="HeaderNavItem", [Raw("float", "right"), MarginLeft(Px(30))]));

module NavLink = (
  val NiceComponents.a(~debugName="HeaderNavLink", [Raw("color", "inherit"), TextDecorationLine(None_)])
);

let make = (_children) => {
  ...component,
  render: (_self) =>
    <Wrapper>
      <PageFrame>
        <Logo> <NavLink props={"href": "/"}> (str_to_ele("30s of Reason")) </NavLink> </Logo>
        <Nav>
          <NavItem>
            <NavLink props={"href": "https://github.com/hehk/30s-of-reason"}> (str_to_ele("Github")) </NavLink>
          </NavItem>
          <NavItem> <NavLink props={"href": "/about"}> (str_to_ele("About")) </NavLink> </NavItem>
        </Nav>
      </PageFrame>
    </Wrapper>
};

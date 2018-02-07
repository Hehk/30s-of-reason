module type Component = {
  open ReasonReact;
  let className: string;
  let component:
    componentSpec(
      stateless,
      stateless,
      noRetainedProps,
      noRetainedProps,
      actionless
    );
  let make:
    (~props: Js.t({..})=?, array(reactElement)) =>
    componentSpec(
      stateless,
      stateless,
      noRetainedProps,
      noRetainedProps,
      actionless
    );
};

let make = (~tag, ~debugName="", styles) : (module Component) =>
  (module
   {
     let component = ReasonReact.statelessComponent(debugName);
     let className = Nice.css(styles);
     let make = (~props=?, children) => {
       ...component,
       render: _self => {
         let cls = {"className": className};
         switch props {
         | None => ReasonReact.createDomElement(tag, ~props=cls, children)
         | Some(x) =>
           ReasonReact.createDomElement(
             tag,
             ~props=Js.Obj.assign(cls, x),
             children
           )
         };
       }
     };
   });

let div = make(~tag="div");

let header = make(~tag="header");

let nav = make(~tag="nav");

let ul = make(~tag="ul");

let ol = make(~tag="ol");

let li = make(~tag="li");

let a = make(~tag="a");

let p = make(~tag="p");

let code = make(~tag="code");

let h1 = make(~tag="h1");

let h2 = make(~tag="h2");

let h3 = make(~tag="h3");

let h4 = make(~tag="h4");

let h5 = make(~tag="h5");

let h6 = make(~tag="h6");

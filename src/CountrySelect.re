open BsReactSelect;

[%bs.raw {|require('flag-icon-css/css/flag-icon.min.css')|}];
[%bs.raw {|require('react-select/dist/react-select.css')|}];

type t = {
  .
  "value": string,
  "label": string,
};

[@bs.module] external countries: array(t) = "../../../src/countries.json";

type state = {open_: bool};

type action =
  | Open
  | Close;

let component = ReasonReact.reducerComponent(__MODULE__);

let optionRenderer = item =>
  <div className="CountrySelect-row">
    <span
      className={
        "CountrySelect-row-flag-icon flag-icon flag-icon-" ++ item##value
      }
    />
    <span> {item##label |> ReasonReact.string} </span>
  </div>;

let make = (~className="", ~country="", ~onChange=_ => (), _children) => {
  ...component,
  initialState: () => {open_: false},
  reducer: (action, _) =>
    switch (action) {
    | Open => ReasonReact.Update({open_: true})
    | Close => ReasonReact.Update({open_: false})
    },
  render: self =>
    <div>
      <button
        className={"CountrySelect-button" ++ " " ++ className}
        onFocus={_ => self.send(Open)}>
        {
          Js.Array.find(item => item##value == country, countries)
          ->Belt.Option.mapWithDefault("", item => item##label)
          |> ReasonReact.string
        }
      </button>
      {self.state.open_ ?
         <div className="CountrySelect-popup-wrapper">
           <Select
             autoFocus=true
             placeholder={Str("Search")}
             openOnFocus=true
             options=countries
             onChange
             optionRenderer
             arrowRenderer={_ => ReasonReact.null}
             value={country->Select.Option.Str}
             onClose={() => self.send(Close)}
             onFocus={() => self.send(Open)}
           />
         </div> :
         ReasonReact.null}
    </div>,
};

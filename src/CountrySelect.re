open BsReactSelect;

[%bs.raw {|require('flag-icon-css/css/flag-icon.min.css')|}];
[%bs.raw {|require('react-select/dist/react-select.css')|}];

type t = {
  .
  "value": string,
  "label": string,
};

[@bs.module] external countries: array(t) = "../../../src/countries.json";

type state = {
  open_: bool,
  buttonRef: ref(option(Dom.element)),
};

type action =
  | Open
  | KeyDown(int)
  | Close;

let component = ReasonReact.reducerComponent(__MODULE__);

let setButtonRef = (r, {ReasonReact.state}) =>
  state.buttonRef := Js.Nullable.toOption(r);

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
  initialState: () => {open_: false, buttonRef: ref(None)},
  reducer: (action, state) =>
    switch (action) {
    | Open => ReasonReact.Update({...state, open_: true})
    | Close =>
      ReasonReact.UpdateWithSideEffects(
        {...state, open_: false},
        (
          self =>
            switch (self.state.buttonRef^) {
            | Some(_) =>
              %bs.raw
              {|match.focus()|}
            | None => ()
            }
        ),
      )
    | KeyDown(13 | 37 | 38 | 39 | 40) =>
      ReasonReact.SideEffects((self => self.send(Open)))
    | KeyDown(_) => ReasonReact.NoUpdate
    },
  render: self =>
    <div>
      <button
        className={"CountrySelect-button" ++ " " ++ className}
        onClick={_ => self.send(Open)}
        ref={r => self.state.buttonRef := Js.Nullable.toOption(r)}
        onKeyDown={event =>
          self.send(KeyDown(ReactEvent.Keyboard.which(event)))
        }>
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
